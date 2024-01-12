#include "routing.h"
import userdb;
using namespace http;
#include "statistic.h"


struct DrawingPoint {
	std::string color;
	int penWidth;
	double x;
	double y;
	// Add more fields as needed
};


void Routing::Run(Storage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});


	CROW_ROUTE(m_app, "/register")
		.methods("POST"_method)
		([this, &storage](const crow::request& req) {
		crow::json::rvalue jsonData = crow::json::load(req.body);

		// Check if the JSON data was parsed successfully
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}

		// Access JSON data fields (e.g., email, username, password)
		std::string email = jsonData["email"].s();
		std::string username = jsonData["username"].s();
		std::string password = jsonData["password"].s();


		bool isUnique = IsUnique(email, username, password, storage);

		if (isUnique)
		{
			uint16_t id = -1;
			UserDB user(id, email, username, password);
			storage.insert(user);
			return crow::response(200, "Registration successful");
		}
		else
		{
			return crow::response(409, "Registration failed: username/email already exists.");
		}
			});



	CROW_ROUTE(m_app, "/login")
		.methods("PUT"_method)
		([this, &storage](const crow::request& req) {

		crow::json::rvalue jsonData = crow::json::load(req.body);

		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}

		std::string username = jsonData["username"].s();
		std::string password = jsonData["password"].s();

		bool isAuthenticated = AuthentificationCheck(username, password, storage);

		if (isAuthenticated) {
			return crow::response(200, "Login successful");
		}
		else {
			return crow::response(401, "Login failed: username/password incorrect");
		}
			});

	CROW_ROUTE(m_app, "/lobby")
		.methods("PUT"_method)
		([this](const crow::request& req) {
		if (m_gameExists)
		{
			return crow::response(400, "Game creation failed: A game is already in progress.");
		}
		else
		{
			crow::json::rvalue jsonData = crow::json::load(req.body);
			if (!jsonData) {
				return crow::response(400, "Invalid JSON format");
			}

			uint16_t id;
			std::random_device RD; // random device to generate a seed for the random number engine
			std::mt19937 engine(RD()); // Mersenne Twister pseudo-random number engine, seeded with the random device
			std::uniform_int_distribution<> distr(0, 10); // uniform distribution for integers within [0, productions.size() - 1]
			id = distr(engine);

			//create game
			Difficulty dificulty = StringToDifficultyType(jsonData["Difficulty"].s());
			m_game.SetGameID(id);
			std::string username = jsonData["Username"].s();
			Player* player = new Player;
			player->SetUsername(username);
			m_game.AddPlayer(*player);
			m_game.SetDifficulty(dificulty);
			SetGameMaster(player->GetUsername());
			m_gameExists = true;

			//send gameId to the client
			crow::json::wvalue responseJson;
			responseJson["gameId"] = id;
			return crow::response(200, responseJson);
		}
			});




	/*CROW_ROUTE(m_app, "/lobby")
		.methods("GET"_method)
		([this](const crow::request& req) {

		crow::json::rvalue jsonData = crow::json::load(req.body);
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}
		uint16_t id = jsonData["RoomCode"].i();

			});*/

	CROW_ROUTE(m_app, "/playerjoined")
		.methods("PUT"_method)
		([this](const crow::request& req) {

		crow::json::rvalue jsonData = crow::json::load(req.body);
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}
		uint16_t id = jsonData["RoomCode"].i();
		if (id != m_game.GetGameID())
		{
			return crow::response(401, "Room doesn't exist!");
		}
		Player p;
		p.SetUsername(jsonData["username"].s());
		m_game.AddPlayer(p);
		return crow::response(200, "Gud");
			});

	/*CROW_ROUTE(m_app, "/game/role")
		.methods("GET"_method)
		([this](const crow::request& req) {


		crow::json::rvalue jsonData = crow::json::load(req.body);
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}
		std::string username = jsonData["username"].s();
		for (Player p : m_game.getPlayers())
		{
			if (p.GetUsername() == username && p.GetIsDrawer())
			{
				return crow::response(200, "Drawing");
			}
			}
		return crow::response(201, "Not Drawing");
			});*/

	CROW_ROUTE(m_app, "/playerjoined")
		.methods("GET"_method)
		([this](const crow::request& req) {

		crow::json::wvalue jsonResponse;
		std::vector<std::string> playerNames;
		for (const auto& p : m_game.GetPlayers())
		{
			playerNames.push_back(p.first);
		}
		jsonResponse["players"] = playerNames;
		return jsonResponse.dump();
			});

	CROW_ROUTE(m_app, "/profile/addGameToGameHistory")
		.methods("PUT"_method)
		([this, &storage](const crow::request& req) {
		crow::json::rvalue jsonResponse = crow::json::load(req.body);
		std::string username = jsonResponse["username"].s();
		uint16_t score = jsonResponse["score"].i();

		Statistic s{ username,score };

		storage.insert(s);

		return crow::response(200, "Game added to game history");

			});


	CROW_ROUTE(m_app, "/profile")
		.methods("PUT"_method)
		([this, &storage](const crow::request& req) {
		crow::json::rvalue jsonResponse = crow::json::load(req.body);
		std::string username = jsonResponse["username"].s();
		std::vector<int> gameHistory;
		crow::json::wvalue jsonResponse2;


		//inner join

		auto results = storage.select((&Statistic::GetUsername, &Statistic::GetScore),
			sqlite_orm::where(sqlite_orm::is_equal(username, &Statistic::GetUsername)));


		//result
		for (const auto& result : results) {

			gameHistory.emplace_back(result);
		}

		jsonResponse2["gameHistory"] = gameHistory;
		return crow::response(200, jsonResponse2);
			});


	CROW_ROUTE(m_app, "/game")
		.methods("PUT"_method)
		([this,&storage]() {
		
		if (m_game.GetPlayers().size() > 1)
		{
			m_game.SetLobbyState(LobbyState::Starting);
			PopulateVectorWords(storage);
			m_game.UpdateWords();
			m_game.StartGame(m_app);
			return crow::response(200, "Game is finished");
		}
		else
		{
			return crow::response(400, "Not enough players!");
		}
			});

	CROW_ROUTE(m_app, "/lobby/waiting")
		.methods("GET"_method)
		([this]() {

		if (m_gameExists)
		{
			if (m_game.GetLobbyState() == LobbyState::Starting)
			{
				return crow::response(200, "Game has started");
			}
			else
			{
				return crow::response(201, "Game is still waiting");
			}
		}
		else
		{
			return crow::response(404, "Game not found");
		}



			});

	CROW_ROUTE(m_app, "/game/startround")
		.methods("GET"_method)
		([this](const crow::request& req) {

		crow::json::rvalue jsonData = crow::json::load(req.body);
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}

		std::string username = jsonData["username"].s();

		crow::json::wvalue responseJson;
		responseJson["word"] = m_currentWord;
		bool isDrawing = false;
		for (auto& p : m_game.GetPlayers())
		{
			if (p.first == username && p.second.GetIsDrawer())
			{
				isDrawing = true;
			}
		}
		responseJson["isDrawing"] = isDrawing;
		return crow::response(200, responseJson);
			});

	CROW_ROUTE(m_app, "/game/startround")
		.methods("PUT"_method)
		([this](const crow::request& req)
			{

				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData) {
					return crow::response(400, "Invalid JSON format");
				}

				std::string m_currentword = jsonData["word"].s();

				return crow::response(200, "Word is ok!");
			});

	CROW_ROUTE(m_app, "/game/tryguess")
		.methods("PUT"_method)
		([this](const crow::request req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData) {
					return crow::response(400, "Invalid JSON format");
				}
				std::string tryGuess = jsonData["Guess"].s();
				std::string username = jsonData["username"].s();
				crow::json::wvalue responseJson;
				if (m_game.GetPlayers()[username].GetHasGuessed()==false)
				{
					if (tryGuess == m_wordDrawer)
					{
						m_game.GetRoundRef().GetSubRoundRef().SetGuessed(true);
						m_game.SetPlayerHasGuessed(username, true);
						return crow::response(200, "Guessed");
					}
				}
				else
				{
					return crow::response(203, "Already guessed");
				}
					
				return crow::response(201, "Wrong");

			});

	CROW_ROUTE(m_app, "/game/getword")
		.methods("PUT"_method)
		([this](const crow::request req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData) {
					return crow::response(400, "Invalid JSON format");
				}
				m_currentWord = jsonData["currentword"].s();
				m_wordDrawer = jsonData["wordDrawer"].s();
				std::cout << "\n" << m_wordDrawer << "\n";
				return crow::response(200, "Word is ok");
			});

	CROW_ROUTE(m_app, "/game/package")
		.methods("GET"_method)
		([this](const crow::request req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData) {
					return crow::response(400, "Invalid JSON format");
				}
				crow::json::wvalue responseJson;
				std::string username = jsonData["username"].s();
				if (m_game.GetPlayers()[username].GetIsDrawer())
				{
					responseJson["isDrawing"] = true;
					responseJson["word"] = m_wordDrawer;
					std::cout << "\n" << m_wordDrawer << "\n";
				}
				else
				{
					responseJson["isDrawing"] = false;
					responseJson["word"] = m_currentWord;
				}
				//for (const auto& pair : m_game.GetPlayers()) {
				//	const Player& p = pair.second; // Access the Player object from the key-value pair
				//	if (p.GetUsername() == username && p.GetIsDrawer()) {
				//		return crow::response(200, "Drawing");
				//	}
				//}
				return crow::response(200, responseJson);
			});

	CROW_ROUTE(m_app, "/game/difficulty")
		.methods("GET"_method)
		([this]()
			{
				if (m_gameExists)
				{
					crow::json::wvalue responseJson;
					responseJson["Difficulty"] = DifficultyTypeToString(m_game.GetDifficulty());
					return crow::response(200, responseJson);
				}
				else
				{
					return crow::response(404, "Game not found");
				}
			});

	CROW_ROUTE(m_app, "/game/pixel")
		.methods("PUT"_method)
		([this](const crow::request req)
			{
				DrawingPoint drawingPoint;
				if (req.body.size() >= sizeof(int) + sizeof(float) * 2 + sizeof(char))
				{
					std::memcpy(&drawingPoint.penWidth, req.body.data(), sizeof(int));
					std::memcpy(&drawingPoint.x, req.body.data() + sizeof(int), sizeof(double));
					std::memcpy(&drawingPoint.y, req.body.data() + sizeof(int) + sizeof(double), sizeof(double));

					// Extract color (up to 256 characters)
					char colorBuffer[256];
					std::memcpy(colorBuffer, req.body.data() + sizeof(int) + sizeof(double) * 2, sizeof(char) * 256);
					drawingPoint.color.assign(colorBuffer, strnlen(colorBuffer, 256));

					return crow::response(200);
				}
				else
				{
					return crow::response(400,"Invalid Binary Data");
				}
			});

	m_app.port(18080).multithreaded().run();
}



bool http::Routing::IsUnique(std::string email, std::string username, std::string password, Storage& storage)
{
	UserDB userToCheck(-1, email, username, password);

	auto allUsers = storage.get_all<UserDB>();
	if (allUsers.empty())
		return true;
	for (const UserDB& user : allUsers)
	{
		if (userToCheck == user)
		{
			return false;
		}
	}
	return true;
}

bool http::Routing::AuthentificationCheck(std::string username, std::string password, Storage& storage)
{

	UserDB userToCheck(-1, "", username, password);
	auto allUsers = storage.get_all<UserDB>();
	for (const auto& user : allUsers)
	{
		if (user.GetUsername() == userToCheck.GetUsername() && user.GetPassword() == userToCheck.GetPassword())
			return true;
	}
	return false;
}

bool http::Routing::GetGameExists() const
{
	return m_gameExists;
}

void http::Routing::SetGameExists(const bool& gameExists)
{
	m_gameExists = gameExists;
}

void http::Routing::SetGameMaster(const std::string& name)
{
	m_gameMaster = name;
}

std::string http::Routing::GetGameMaster() const
{
	return m_gameMaster;
}

bool http::Routing::IsGameMaster(const std::string& name)
{
	if (m_gameMaster == name)
		return true;
	return false;
}

void http::Routing::SetCurrentWord(const std::string& word)
{
	m_currentWord = word;
}

std::string http::Routing::GetCurrentWord() const
{
	return m_currentWord;
}


void http::Routing::PopulateVectorWords(Storage& storage)
{
	std::vector<Word> wordsVector;
	for (int i = 0; i < 4 * m_game.GetPlayers().size(); i++)
	{
		Difficulty dif = m_game.GetDifficulty();
		std::random_device RD;
		std::mt19937 engine(RD());
		
		std::uniform_int_distribution<> distr;
		if (dif == Difficulty::Easy)
		{
			distr = std::uniform_int_distribution<>(1, 200);

		}
		else if (dif == Difficulty::Medium)
		{
			distr = std::uniform_int_distribution<>(201, 400);

		}
		else {
			distr = std::uniform_int_distribution<>(401, 500);
		}
		int id = distr(engine);
		auto results = storage.get_all<Word>(sqlite_orm::where(sqlite_orm::c(&Word::GetId) == id));
		if (!results.empty())
		{
			const auto& row = results.front();
			wordsVector.emplace_back(row);
		}
	}
	//for(word)
	m_game.SetWords(wordsVector);
}