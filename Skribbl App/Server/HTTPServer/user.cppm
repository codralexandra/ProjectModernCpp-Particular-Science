module;
export module user;
import <cstdint>;
import <string>;
import <queue>;
import<iostream>;

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
		~User();

		std::string GetEmail() const;
		std::string GetUsername() const;
		std::string GetPassword() const;
		//std::queue<std::pair<uint16_t, std::string>> GetGameHistory() const;
		uint16_t GetPersonalBest() const;

		void SetEmail(const std::string& email);
		void SetUsername(std::string username);
		void SetPassword(const std::string& password);
		//void SetGameHistory(const std::queue<std::pair<uint16_t, std::string>>& gameHistory);
		void SetPersonalBest(const uint16_t& personalBest);

		//void AddGameToGameHistory(std::pair<uint16_t, std::string> game);
	private:
		std::string m_username;
		std::string m_email;
		std::string m_password;
		//std::queue<std::pair<uint16_t, std::string>> m_gameHistory;
		uint16_t m_personalBest;
	};
}