#include "routing.h"

using namespace http;

void Routing::Run()
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});


    CROW_ROUTE(m_app, "/register")
        .methods("POST"_method)
        ([](const crow::request& req) {
        auto bodyArgs = parseUrlArgs(req.body);
        auto end = bodyArgs.end();
        auto usernameIter = bodyArgs.find("username");
        auto emailIter = bodyArgs.find("email");
        auto passwordIter = bodyArgs.find("password");
        if (usernameIter != end && emailIter != end && passwordIter != end)
        {
            //add to database
            std::cout << usernameIter->second << " ";
        }
        return crow::response(200);;
        });

    CROW_ROUTE(m_app, "/login")
        .methods("POST"_method)
        ([](const crow::request& req) {
        auto bodyArgs = parseUrlArgs(req.body);
        auto end = bodyArgs.end();
        auto usernameIter = bodyArgs.find("username");
        auto passwordIter = bodyArgs.find("password");
        if (usernameIter != end && passwordIter != end) {
           // bool isAuthenticated = checkUser(usernameIter->second, passwordIter->second);
            bool isAuthenticated = true;
            if (isAuthenticated) {
                return crow::response(200, "Login successful");
            }
            else {
                return crow::response(401, "Unauthorized");
            }
        }
        else {
            return crow::response(400, "Bad Request");
        }
      });


	m_app.port(18080).multithreaded().run();
}