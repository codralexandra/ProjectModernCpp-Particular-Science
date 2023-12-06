#include <filesystem>
#include <iostream>
#include <memory>
#include "Word.h"
#include "routing.h"
#include <sqlite_orm/sqlite_orm.h>

using namespace http;
#include <crow.h>
#include "gamedata.h"
namespace sql = sqlite_orm;


// Cerinte:
// Sa se creeze si sa se populeze baza de date.
// Sa se creeze un server http cu urmatoarele rute:
//	/products  -> se vor trimite clientului produsele (vector, json)
//  /addproducttobasket/<id>?quantity=<value>  -> se va adauga un produs in cosul de cumparaturi (URL params)
//  /addproducttobasket  -> se va adauga un produs in cosul de cumparaturi (POST/PUT)
//  /basket  -> se trimit clientului produsele din cos (nume, pret, cantitate)


int main() 
{
	
	Word w("Ice-cream","EASY",1);
	std::cout<<w.getValueAux()<<" "<<w.getNumberHint()<<std::endl;
	w.ShowHint();
	w.ShowHint();
	w.ShowHint();

	Storage db = createStorage("Words.sqlite");
	try {
		db.sync_schema();
	}
	catch (const std::exception& e) {
		std::cerr << "Error during schema sync: " << e.what() << std::endl;
	}
	
	auto initialWordsCount = db.count<Word2>();
	if (initialWordsCount == 0)
	{
		populateStorage(db);

	}
	std::cout << db.count<Word2>() << std::endl;

	crow::SimpleApp app;
	CROW_ROUTE(app, "/")([]() {

		return "MEAW";
		}
	);
	CROW_ROUTE(app, "/words")([&db]() {

		std::vector<crow::json::wvalue>wordsJson;
		for (const auto& word : db.iterate<Word2>())
		{
			crow::json::wvalue wordJson{
				{"id", word.m_id},
				{ "name",word.m_value},
				{ "difficulty",word.m_difficulty }

			};
			wordsJson.push_back(wordJson);
		}
		return crow::json::wvalue(wordsJson);
		});
	app.port(18080).multithreaded().run();

	/*Routing r;
	r.Run();
	return 0;*/
}