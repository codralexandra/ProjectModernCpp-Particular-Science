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
	//std::cout << "I installed sqlite_orm and crow. Now, the sky is the limit!" /*🌌🚀*/ << std::endl;
	/*Word w("table","EASY",1);
	std::cout<<w.getValueAux()<<" "<<w.getNumberHint()<<std::endl;
	w.ShowHint();
	w.ShowHint();
	w.ShowHint();*/

	Storage db = createStorage("Game.sqlite");
	db.sync_schema();  //crapa la sinc de ce???
	auto initialProductsCount = db.count<Word2>();
	if (initialProductsCount == 0)
	{
		populateStorage(db);

	}
	std::cout << db.count<Word2>() << std::endl;
	/*Routing r;
	r.Run();*/
	return 0;
}