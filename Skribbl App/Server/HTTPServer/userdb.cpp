import userdb;
using Scribble::UserDB;

UserDB::UserDB()
{
	m_id = -1;
	m_username = "";
	m_password = "";
}

Scribble::UserDB::UserDB(const uint16_t id, const std::string& username, const std::string password)
{
	m_id = id;
	m_username = username;
	m_password = password;
}

UserDB Scribble::UserDB::ConvertToUserDB(const Scribble::User& user)
{
	this->m_id = -1;
	this->m_username = user.GetUsername();
	this->m_password = user.GetPassword();
	return *this;
}

void Scribble::UserDB::SetId(const uint16_t& id)
{
	m_id = id;
}

void Scribble::UserDB::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void Scribble::UserDB::SetPassword(const std::string& password)
{
	this->m_password = password;
}

uint16_t Scribble::UserDB::GetId() const
{
	return m_id;
}

std::string Scribble::UserDB::GetUsername() const
{
	return m_username;
}

std::string Scribble::UserDB::GetPassword() const
{
	return m_password;
}
