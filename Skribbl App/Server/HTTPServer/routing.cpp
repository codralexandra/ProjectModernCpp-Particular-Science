#include "routing.h"

using namespace http;

void Routing::Run()
{
	CROW_ROUTE(m_app, "/register")([]() {
		return "This is an example app of crow and sql-orm";
		});


	m_app.port(18080).multithreaded().run();
}