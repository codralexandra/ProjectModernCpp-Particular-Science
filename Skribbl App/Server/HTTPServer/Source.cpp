#include <filesystem>
#include <iostream>
#include <memory>
#include "Word.h"
//
//#include <crow.h>
//#include <sqlite_orm/sqlite_orm.h>
//namespace sql = sqlite_orm;


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
	Word w("table","EASY");
	std::cout<<w.getValueAux()<<" "<<w.getNumberHint()<<std::endl;
	w.ShowHint();
	w.ShowHint();
	w.ShowHint();
	return 0;
}