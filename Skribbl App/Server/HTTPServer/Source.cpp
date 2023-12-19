#include <filesystem>
#include <iostream>
#include <memory>
#include "Word.h"
#include "routing.h"
#include <sqlite_orm/sqlite_orm.h>
#include "game.h"
#include <crow.h>
#include "gamedata.h"
namespace sql = sqlite_orm;
using namespace http;



int main() 
{
	//Storage db = CreateStorage("Words.sqlite");
	//try {
	//	db.sync_schema();
	//}
	//catch (const std::exception& e) {
	//	std::cerr << "Error during schema sync: " << e.what() << std::endl;
	//}
	//
	//auto initialWordsCount = db.count<Word>();
	//if (initialWordsCount == 0)
	//{
	//	populateStorage(db);
	//}
	//crow::SimpleApp app;
	//CROW_ROUTE(app, "/")([]() {

	//	return "MEAW";
	//	}
	//);
	//CROW_ROUTE(app, "/words")([&db]() {

	//	std::vector<crow::json::wvalue>wordsJson;
	//	for (const auto& word : db.iterate<Word>())
	//	{
	//		crow::json::wvalue wordJson{
	//			{"id", word.getId()},
	//			{ "name",word.getValue()},
	//			{ "difficulty",word.getDifficulty()}

	//		};
	//		wordsJson.push_back(wordJson);
	//	}
	//	return crow::json::wvalue(wordsJson);
	//	});
	////app.port(18080).multithreaded().run();

	//Routing r;
	//r.Run(db);

	Game g;
	Player p,q;
	p.SetUsername("allala");
	q.SetUsername("lalla");
	std::vector<Player> v;
	v.push_back(p);
	v.push_back(q);
	g.setPlayers(v);
	g.Start_Game();
	Player a = g.Winner();
	std::cout << a.GetUsername();
	return 0;
}