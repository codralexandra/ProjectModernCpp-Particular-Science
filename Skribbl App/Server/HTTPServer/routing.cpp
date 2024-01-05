#include "routing.h"
import userdb;
using namespace http;

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
			m_gameExists = true;

			//send gameId to the client
			crow::json::wvalue responseJson;
			responseJson["gameId"] = id;
			return crow::response(200, responseJson);
		}
			});

	CROW_ROUTE(m_app, "/lobby")
		.methods("GET"_method)
		([this](const crow::request& req) {

		crow::json::rvalue jsonData = crow::json::load(req.body);
		if (!jsonData) {
			return crow::response(400, "Invalid JSON format");
		}
		uint16_t id = jsonData["RoomCode"].i();
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
		return crow::response(400, "Joined Successfully");
			});

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

	//Method 2 - more efficient but doesnt work

	/*
	auto emailCondition = sqlite_orm::c(&UserDB::GetEmail) == userToCheck.GetEmail();
	auto usernameCondition = sqlite_orm::c(&UserDB::GetUsername) == userToCheck.GetUsername();
	auto passwordCondition = sqlite_orm::c(&UserDB::GetPassword) == userToCheck.GetPassword();


	auto matchingUsers = storage.get_all<UserDB>(
		sqlite_orm::where(emailCondition) and
		sqlite_orm::where(usernameCondition) &&
		sqlite_orm::where(passwordCondition)
	);*/
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


