module;
export module user;
import <string>;
//import "statistic.h";
import <cstdint>;
import <stack>;
import <iostream>;
namespace Scribble
{
	export class User
	{
	public:
		User();
		User(const std::string& email, const std::string& username, const std::string& password, 
			 const uint16_t& personalBest);
		//friend std::ostream& operator<<(std::ostream& ostream, const User& user); //trebe facuta virtuala 
		User& operator=(const User& user);
		User(const User& user);
		bool validateUserEmail() const;
		bool validateUserPassword() const;
		~User()=default;

		std::string GetEmail() const;
		std::string GetUsername() const;
		std::string GetPassword() const;
		uint16_t GetPersonalBest() const;

		void SetEmail(const std::string& email);
		void SetUsername(std::string username);
		void SetPassword(const std::string& password);
		void SetPersonalBest(const uint16_t& personalBest);

		//void AddGameToGameHistory();
	private:
		std::string m_username;
		std::string m_email;
		std::string m_password;
		uint16_t m_personalBest;
	};
}