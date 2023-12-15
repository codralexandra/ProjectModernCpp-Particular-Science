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


		bool isUnique = IsUnique(email,username,password,storage);

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
		([this,&storage](const crow::request& req) {

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


	m_app.port(18080).multithreaded().run();
}



bool http::Routing::IsUnique(std::string email, std::string username, std::string password,Storage& storage)
{
	UserDB userToCheck(-1, email, username, password);

	auto allUsers = storage.get_all<UserDB>();
	if (allUsers.empty())
		return true;
	for (const auto& user : allUsers)
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



crow::response http::Routing::Register(const crow::request& req, Storage& storage) const
{


	return crow::response(200, "Received and processed JSON data");
}