#pragma once
#include <crow.h>
#include<iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "gamedata.h"
#include "game.h"
#include <random>
#include<queue>
#include "Color.h"

import utils;

namespace http
{
	template <typename T>
	class Routing
	{
		
		struct DrawingPoint {
			
			T color;
			int penWidth;
			double x;
			double y;
			int newLine;
			
		};
	public:
		void Run(Storage& storage);

		bool IsUnique(std::string email, std::string username, std::string password, Storage& storage);
		bool AuthentificationCheck(std::string username, std::string password, Storage& storage);

		bool GetGameExists() const;
		void SetGameExists(const bool& gameExists);

		void SetGameMaster(const std::string& name);
		std::string GetGameMaster() const;
		bool IsGameMaster(const std::string& name);

		void SetCurrentWord(const std::string& word);
		std::string GetCurrentWord() const;

		void PopulateVectorWords(Storage& storage);

	private:
		crow::SimpleApp m_app;
		bool m_gameExists;
		Game m_game;
		std::string m_gameMaster;
		std::string m_currentWord; 
		std::string m_wordDrawer;
		std::pair<double, double> m_pixel;
		int m_penWidth;
		int m_x;
		int m_y;
		bool m_isPixel;
		std::queue<DrawingPoint> m_pixelQueue;
	};
}

