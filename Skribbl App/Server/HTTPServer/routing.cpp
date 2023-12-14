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
        ([this,&storage](const crow::request& req) {
        crow::json::rvalue jsonData = crow::json::load(req.body);

        // Check if the JSON data was parsed successfully
        if (!jsonData) {
            return crow::response(400, "Invalid JSON format");
        }

        // Access JSON data fields (e.g., email, username, password)
        std::string email = jsonData["email"].s();
        std::string username = jsonData["username"].s();
        std::string password = jsonData["password"].s();
        std::cout << email << "\n";
        uint16_t id = -1;
        UserDB user(id, username, password);
        storage.insert(user);
        return crow::response(200);;
        });

    CROW_ROUTE(m_app, "/login")
        .methods("PUT"_method)
        ([](const crow::request& req) {
        crow::json::rvalue jsonData = crow::json::load(req.body);
        std::string username = jsonData["username"].s();
        std::string password = jsonData["password"].s();
           // bool isAuthenticated = checkUser(usernameIter->second, passwordIter->second);
        bool isAuthenticated = false;
        if (isAuthenticated) {

            return crow::response(200, "Login successful");
        }
        else {
            return crow::response(401, "Unauthorized");
        }
      });


	m_app.port(18080).multithreaded().run();
}

//crow::response http::Routing::Register(const crow::request& req, Storage& storage) const
//{
//    auto bodyArgs = parseUrlArgs(req.body);
//    auto end = bodyArgs.end();
//    auto usernameIter = bodyArgs.find("username");
//    auto emailIter = bodyArgs.find("email");
//    auto passwordIter = bodyArgs.find("password");
//    if (usernameIter != end && emailIter != end && passwordIter != end)
//    {
//        UserDB user(usernameIter->second, passwordIter->second);
//        storage.replace(user);        
//    }
//    return crow::response(200, "Register Successful");
//}


crow::response http::Routing::Register(const crow::request& req, Storage& storage) const
{
    

    return crow::response(200, "Received and processed JSON data");
}