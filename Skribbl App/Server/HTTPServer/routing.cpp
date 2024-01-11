#include "routing.h"
import userdb;
using namespace http;
#include "statistic.h"

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
		for (const Player& p : m_game.getPlayers())
		{
			playerNames.push_back(p.GetUsername());
		}
		jsonResponse["players"] = playerNames;
		return jsonResponse.dump();
			});
	//

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
		([this,&storage](const crow::request& req) {
		crow::json::rvalue jsonResponse=crow::json::load(req.body);
		std::string username = jsonResponse["username"].s();
		std::vector<int> gameHistory;
		crow::json::wvalue jsonResponse2;


		//inner join
		
		auto results = storage.select(( &UserDB::GetUsername, &Statistic::GetScore ),
			sqlite_orm::inner_join<User>(sqlite_orm::on(sqlite_orm::is_equal(&UserDB::GetUsername, &Statistic::GetUsername))));


		//result
		for (const auto& result : results) {
			
			gameHistory.emplace_back(result);
		}

		jsonResponse2["gameHistory"] = gameHistory;
		return crow::response(200,jsonResponse2);
			});


	CROW_ROUTE(m_app, "/game")
		.methods("PUT"_method)
		([this,&storage]() {
		
		if (m_game.getPlayers().size() > 1)
		{
			m_game.SetLobbyState(LobbyState::Starting);
			PopulateVectorWords(storage);
			m_game.Start_Game(m_app);
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
		//responseJson["word"] = ;
		bool isDrawing = false;
		for (Player p : m_game.getPlayers())
		{
			if (p.GetUsername() == username && p.GetIsDrawer())
			{
				isDrawing = true;
			}
		}
		responseJson["isDrawing"] = isDrawing;
		return crow::response(200, responseJson);
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
				crow::json::wvalue responseJson;
				if (tryGuess == m_currentWord)
				{
					responseJson["ResponseMsg"] = "Accepted";
					return crow::response(200, responseJson);
				}
				else
				{
					responseJson["ResponseMsg"] = "Denied";
					return crow::response(200, responseJson);
				}
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
	for (int i = 0; i < 4 * m_game.getPlayers().size(); i++)
	{
		Difficulty dif = m_game.GetDifficulty();
		std::random_device RD;
		std::mt19937 engine(RD());
		int numberOfElements;
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
		auto results = storage.get_all<Word>(sqlite_orm::where(sqlite_orm::c(&Word::getId) == id));
		if (!results.empty())
		{
			const auto& row = results.front();
			wordsVector.push_back(row);
		}
	}
	m_game.setWords(wordsVector);
}