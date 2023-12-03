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
        }
        return crow::response(200);;
            });


	m_app.port(18080).multithreaded().run();
}