export module userdb;
import user;
import<string>;

namespace Scribble
{
	export class UserDB
	{
	public:
		UserDB();
		UserDB ConvertToUserDB(const Scribble::User& user);


	public:
		std::string m_username;
		std::string m_password;
	};
}
