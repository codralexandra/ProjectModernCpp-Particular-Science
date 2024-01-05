module;
export module user;
import <string>;
import "statistic.h";
//#include "statistic.h"
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
			 const uint16_t& personalBest, const std::stack<Statistic>&gameHistory);
		//friend std::ostream& operator<<(std::ostream& ostream, const User& user); //trebe facuta virtuala 
		User& operator=(const User& user);
		User(const User& user);
		bool validateUserEmail() const;
		bool validateUserPassword() const;
		~User()=default;

		std::string GetEmail() const;
		std::string GetUsername() const;
		std::string GetPassword() const;
		//std::stack<Statistic> GetGameHistory() const;
		uint16_t GetPersonalBest() const;

		void SetEmail(const std::string& email);
		void SetUsername(std::string username);
		void SetPassword(const std::string& password);
		//void SetGameHistory(const std::stack<Statistic>& gameHistory);
		void SetPersonalBest(const uint16_t& personalBest);

		void AddGameToGameHistory();
	private:
		std::string m_username;
		std::string m_email;
		std::string m_password;
		//Statistic* a=new Statistic("aa",12);
		std::stack<Statistic> m_gameHistory;
		uint16_t m_personalBest;
	};
}