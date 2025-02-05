#include "routing.h"
import userdb;
using namespace http;
#include "statistic.h"
#include<thread>

void http::Routing<int>::Run(Storage& storage)
{	
	//--------------------------
	//     REGISTER AND LOGIN
	//--------------------------

	CROW_ROUTE(m_app, "/register")
		.methods("POST"_method)
		([this, &storage](const crow::request& req) {
		crow::json::rvalue jsonData = crow::json::load(req.body);

		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}

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

	//--------------------------
	//   CREATE AND JOIN GAME
	//--------------------------
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
			std::random_device RD; 
			std::mt19937 engine(RD()); 
			std::uniform_int_distribution<> distr(0, 10); 
			id = distr(engine);


			Difficulty dificulty = StringToDifficultyType(jsonData["Difficulty"].s());
			m_game.SetGameID(id);
			std::string username = jsonData["Username"].s();
			Player* player = new Player;
			player->SetUsername(username);
			m_game.AddPlayer(*player);
			m_game.SetDifficulty(dificulty);
			SetGameMaster(player->GetUsername());
			m_gameExists = true;


			crow::json::wvalue responseJson;
			responseJson["gameId"] = id;
			return crow::response(200, responseJson);
		}
			});


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


	//--------------------------
	// GAME HISTORY AND PROFILE
	//--------------------------
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

		auto results = storage.select((&Statistic::GetUsername, &Statistic::GetScore),
			sqlite_orm::where(sqlite_orm::is_equal(username, &Statistic::GetUsername)));

		for (const auto& result : results) {

			gameHistory.emplace_back(result);
		}

		jsonResponse2["gameHistory"] = gameHistory;
		return jsonResponse2.dump();
			});

	
	CROW_ROUTE(m_app, "/game/playerScores").methods("GET"_method)([this]() {
		crow::json::wvalue jsonSendPackage;
		std::vector<int> playerScores;
		std::vector<std::string> playersUsernames;
		for(const auto& it : m_game.GetPlayers())
		{
			playerScores.push_back(it.second.GetPersonalScore());
			playersUsernames.push_back(it.first);
			std::cout << "\n\n\n\n\n" << it.first << " " << it.second.GetPersonalScore() << "\n\n\n\n";
		}

		jsonSendPackage["playerScores"] = playerScores;
		jsonSendPackage["playersUsernames"] = playersUsernames;
		return crow::response(200, jsonSendPackage);
		});
		

	//--------------------------
	//      DRAWING WIDGET
	//--------------------------

	CROW_ROUTE(m_app, "/game/pixel")
		.methods("PUT"_method)
		([this](const crow::request req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData) {
					return crow::response(400, "Invalid JSON format");
				}
				DrawingPoint point;
				point.color = HexStringToColorPosition(jsonData["color"].s());
				point.penWidth = jsonData["penWidth"].i();
				point.x = jsonData["x"].d();
				point.y = jsonData["y"].d();
				bool newLineBool = jsonData["newLine"].b();
				point.newLine = newLineBool ? 1 : 0;
				/*m_color = jsonData["color"].s();
				m_penWidth = jsonData["penWidth"].i();
				m_x = jsonData["x"].d();
				m_y = jsonData["y"].d();*/
				m_pixelQueue.push(point);
				m_isPixel = true;
				//std::cout << "\n" << point.x << " " << point.y << " " << point.penWidth << " " << point.color <<" "<< m_pixelQueue.size() <<" " << point.newLine<<"\n";
				return crow::response(200, "Pixel recived");

			});

	//--------------------------
	//      GAME STATUS
	//--------------------------

	CROW_ROUTE(m_app, "/game")
		.methods("PUT"_method)
		([this, &storage]() {

		if (m_game.GetPlayers().size() > 1)
		{
			m_game.SetLobbyState(LobbyState::Starting);
			PopulateVectorWords(storage);
			m_game.UpdateWords();
			m_game.StartGame(m_app,m_game.GetDifficulty());
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
				if (!m_pixelQueue.empty())
					{
					//m_game.SetPlayerReceivedPixels(username, true);
					//std::cout<<"\n\n\n\n\n\n\n"<<m_game.GetPlayers()[username].GetHasReceivedPixels()<<"\n\n\n\n\n\n\n";
					std::queue<DrawingPoint> copyQueue = m_pixelQueue;
					//bool emptyThePixelQueue = true;
					//for (auto& p : m_game.GetPlayers())
					//{
					//	//std::cout << p.second.GetUsername() << " " << p.second.GetHasReceivedPixels() << "\n";
					//	if (!p.second.GetHasReceivedPixels() && !p.second.GetIsDrawer())
					//	{
					//		emptyThePixelQueue = false;
					//	}
					//}
					/*if (emptyThePixelQueue)
					{
						m_pixelQueue = std::queue<DrawingPoint>();
						for (auto& p : m_game.GetPlayers())
						{
							m_game.SetPlayerReceivedPixels(p.first, false);
						}
					}*/
					std::vector<double> x;
					std::vector<double> y;
					std::vector<int> penWidth;
					std::vector<int> colors;
					std::vector<std::string> colorsHex;
					std::vector<int> newLine;
					while (!copyQueue.empty())
					{
						DrawingPoint point = copyQueue.front();
						m_pixelQueue.pop();
						copyQueue.pop();
						x.push_back(point.x);
						y.push_back(point.y);
						colors.push_back(point.color);
						penWidth.push_back(point.penWidth);
						newLine.push_back(point.newLine);
					}
					//cout << x.size();
					/*DrawingPoint point = m_pixelQueue.front();
					m_pixelQueue.pop();*/
					responseJson["x"] = x;
					responseJson["y"] = y;
					responseJson["penWidth"] = penWidth;
					for (int& color : colors)
					{
						colorsHex.push_back(ColorToHexString(color));
					}
					responseJson["color"] = colorsHex;
					responseJson["newLine"] = newLine;
					std::cout << "\n\n TRIMIS " << username << "\n\n";
				}
				if (m_game.GetGameEnded() == true)
				{
					/*responseJson["GameState"] = true;
					std::vector<int> playerScores;
					std::vector<std::string> playersUsernames;
					for (const auto& it : m_game.GetPlayers())
					{
						playerScores.push_back(it.second.GetPersonalScore());
						playersUsernames.push_back(it.first);
					}
					responseJson["playerScores"] = playerScores;
					responseJson["playersUsernames"] = playersUsernames;*/
					return crow::response(202, responseJson);
				}
				return crow::response(200, responseJson);
			});


	//--------------------------
	//          WORD 
	//--------------------------

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
				if (m_game.GetPlayers()[username].GetHasGuessed() == false)
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

	m_app.port(18080).multithreaded().run();
}

template <>
bool http::Routing<int>::IsUnique(std::string email, std::string username, std::string password, Storage& storage)
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

template <>
bool http::Routing<int>::AuthentificationCheck(std::string username, std::string password, Storage& storage)
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

bool http::Routing<int>::GetGameExists() const
{
	return m_gameExists;
}

void http::Routing<int>::SetGameExists(const bool& gameExists)
{
	m_gameExists = gameExists;
}

template <>
void http::Routing<int>::SetGameMaster(const std::string& name)
{
	m_gameMaster = name;
}

std::string http::Routing<int>::GetGameMaster() const
{
	return m_gameMaster;
}

bool http::Routing<int>::IsGameMaster(const std::string& name)
{
	if (m_gameMaster == name)
		return true;
	return false;
}

void http::Routing<int>::SetCurrentWord(const std::string& word)
{
	m_currentWord = word;
}

std::string http::Routing<int>::GetCurrentWord() const
{
	return m_currentWord;
}

template <>
void http::Routing<int>::PopulateVectorWords(Storage& storage)
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

	m_game.SetWords(wordsVector);
}