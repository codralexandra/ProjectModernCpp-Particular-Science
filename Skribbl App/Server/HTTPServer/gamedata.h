#pragma once
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
import userdb;
namespace sql = sqlite_orm;
using namespace Scribble;
import utils;


inline auto CreateStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word",
			sql::make_column("id", &Word::SetId, &Word::getId, sql::primary_key().autoincrement()),
			sql::make_column("name", &Word::setValue, &Word::getValue),
			sql::make_column("difficulty", &Word::setDifficulty, &Word::getDifficulty)
		),
		sql::make_table(
			"User",
			sql::make_column("id", &UserDB::SetId, &UserDB::GetId, sql::primary_key().autoincrement()),
			sql::make_column("username", &UserDB::SetUsername, &UserDB::GetUsername),
			sql::make_column("password", &UserDB::SetPassword, &UserDB::GetPassword)
		)
		
	);
}

using Storage = decltype(CreateStorage(""));

void populateStorage(Storage& storage);




