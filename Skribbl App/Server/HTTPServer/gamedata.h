#pragma once
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
#include "Statistic.h"
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
			sql::make_column("id", &Word::SetId, &Word::GetId, sql::primary_key().autoincrement()),
			sql::make_column("name", &Word::SetValue, &Word::GetValue),
			sql::make_column("difficulty", &Word::SetDifficulty, &Word::GetDifficulty)
		),
		sql::make_table(
			"User",
			sql::make_column("id", &UserDB::SetId, &UserDB::GetId, sql::primary_key().autoincrement()),
			sql::make_column("email", &UserDB::SetEmail, &UserDB::GetEmail),
			sql::make_column("username", &UserDB::SetUsername, &UserDB::GetUsername),
			sql::make_column("password", &UserDB::SetPassword, &UserDB::GetPassword)
		),
		sql::make_table(
			"GameHistory",
			//sql::make_column("id", &GameHistoryDB::SetId, &GameHistoryDB::GetId, sql::primary_key().autoincrement()),
			sql::make_column("username", &Statistic::SetUsername, &Statistic::GetUsername),
			sql::make_column("score", &Statistic::SetScore, &Statistic::GetScore)
		)
		
	);
}

using Storage = decltype(CreateStorage(""));

void populateStorage(Storage& storage);




