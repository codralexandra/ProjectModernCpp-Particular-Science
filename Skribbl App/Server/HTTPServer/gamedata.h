#pragma once
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
import user;
namespace sql = sqlite_orm;
using namespace Scribble;
import utils;

struct balbla {
	int a, b;
};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		//sql::make_table(
		//	"Word",
		//	sql::make_column("id", &Word::getId(), sql::primary_key().autoincrement()),
		//	sql::make_column("name", &Word::getValue()),
		//	sql::make_column("difficulty", &Word::getDifficulty())
		//	//restul de membrii din word
		//)
		sql::make_table(
			"Word",
			sql::make_column("id", &balbla::a, sql::primary_key().autoincrement()),
			sql::make_column("name", &balbla::b)
			)
		
		
	);
}


