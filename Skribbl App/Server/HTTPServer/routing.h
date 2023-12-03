#pragma once
#include <crow.h>

import utils;

namespace http
{
	class Routing
	{
	public:
		void Run();

	private:
		crow::response Register(const crow::request& req, int productId)const;

	private:
		crow::SimpleApp m_app;
	};
}
