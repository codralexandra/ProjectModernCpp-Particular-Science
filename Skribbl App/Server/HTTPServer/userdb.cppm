export module userdb;
import user;
import<string>;

namespace Scribble
{
	export class UserDB
	{
	public:
		//constructor
		UserDB();
		UserDB(const uint16_t& id, const std::string& email ,const std::string& username, const std::string& password);
		
		//conversion
		UserDB ConvertToUserDB(const Scribble::User& user);

		//setter
		void SetId(const uint16_t& id);
		void SetUsername(const std::string& username);
		void SetPassword(const std::string& password);
		void SetEmail(const std::string& email);

		//getter
		uint16_t GetId() const;
		std::string GetUsername() const;
		std::string GetPassword() const;
		std::string GetEmail() const;

		//operators
		bool operator ==(const UserDB& user) const;


	private:
		uint16_t m_id;
		std::string m_email;
		std::string m_username;
		std::string m_password;
	};


}