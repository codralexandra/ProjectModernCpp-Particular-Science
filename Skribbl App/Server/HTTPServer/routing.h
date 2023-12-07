#pragma once
#include <crow.h>
#include<iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "gamedata.h"

import utils;

namespace http
{
	class Routing
	{
	public:
		void Run(Storage& storage);

	private:
		crow::response Register(const crow::request& req, Storage& storage)const;

	private:
		crow::SimpleApp m_app;
	};
}

