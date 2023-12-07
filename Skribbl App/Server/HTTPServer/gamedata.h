#pragma once
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
import user;
namespace sql = sqlite_orm;
using namespace Scribble;
#include "Word.h"
import user;
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
			sql::make_column("username", &User::SetUsername, &User::GetUsername, sql::primary_key()),
			sql::make_column("password", &User::SetPassword, &User::GetPassword)
		)
		
	);
}

using Storage = decltype(CreateStorage(""));

void populateStorage(Storage& storage);




