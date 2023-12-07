export module userdb;
import user;
import<string>;

namespace Scribble
{
	export class UserDB
	{
	public:
		UserDB();
		UserDB(const uint16_t id,const std::string& username, const std::string password);
		UserDB ConvertToUserDB(const Scribble::User& user);

		void SetId(const uint16_t& id);
		void SetUsername(const std::string& username);
		void SetPassword(const std::string& password);

		uint16_t GetId() const;
		std::string GetUsername() const;
		std::string GetPassword() const;

	public:
		uint16_t m_id;
		std::string m_username;
		std::string m_password;
	};
}
