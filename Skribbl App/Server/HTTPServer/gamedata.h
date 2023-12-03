#pragma once
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
import user;
namespace sql = sqlite_orm;
using namespace Scribble;
import utils;

struct Word2 {
	uint16_t m_id;
	std::string m_value;
	std::string m_difficulty;
};

struct User2 {
	std::string m_email;
	std::string m_password;
};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word2",
			sql::make_column("id", &Word2::m_id, sql::primary_key().autoincrement()),
			sql::make_column("name", &Word2::m_value),
			sql::make_column("difficulty", &Word2::m_difficulty)
		),
		sql::make_table(
			"User2",
			sql::make_column("username", &User2::m_email, sql::primary_key()),
			sql::make_column("password", &User2::m_password)
		)
		
	);
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);




