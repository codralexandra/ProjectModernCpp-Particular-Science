#pragma once
#include <crow.h>
#include<iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "gamedata.h"
#include "game.h"
#include <random>

import utils;

namespace http
{
	class Routing
	{
	public:
		void Run(Storage& storage);
		bool IsUnique(std::string email, std::string username, std::string password, Storage& storage);
		bool AuthentificationCheck(std::string username, std::string password, Storage& storage);
		bool GetGameExists() const;
		void SetGameExists(const bool& gameExists);

		void SetGameMaster(const std::string& name);
		std::string GetGameMaster() const;
		bool IsGameMaster(const std::string& name);


	private:
		crow::SimpleApp m_app;
		bool m_gameExists;
		Game m_game;
		std::string m_gameMaster;
	};
}

