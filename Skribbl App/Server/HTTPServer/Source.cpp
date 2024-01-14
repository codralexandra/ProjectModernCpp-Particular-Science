#include <filesystem>
#include <iostream>
#include <memory>
#include "Word.h"
#include "routing.h"
#include <sqlite_orm/sqlite_orm.h>
#include "game.h"
#include <crow.h>
#include "gamedata.h"
#include "Color.h"
namespace sql = sqlite_orm;
using namespace http;



int main() 
{
	Storage db = CreateStorage("Words.sqlite");
	try {
		db.sync_schema();
	}
	catch (const std::exception& e) {
		std::cerr << "Error during schema sync: " << e.what() << std::endl;
	}
	
	auto initialWordsCount = db.count<Word>();
	if (initialWordsCount == 0)
	{
		populateStorage(db);
	}
	crow::SimpleApp app;
	
	http::Routing<Color> r;
	r.SetGameExists(false);
	r.Run(db);

}