import userdb;
using Scribble::UserDB;

UserDB::UserDB()
{
	m_username = "";
	m_password = "";
}

UserDB Scribble::UserDB::ConvertToUserDB(const Scribble::User& user)
{
	
	this->m_username = user.GetUsername();
	this->m_password = user.GetPassword();
	return this;
}
