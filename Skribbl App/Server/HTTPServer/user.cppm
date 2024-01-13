module;
export module user;
import <string>;
import <cstdint>;
import <iostream>;
namespace Scribble
{
	export class User
	{
	public:
		//constructor and destructor
		User();
		User(const std::string& email, const std::string& username, const std::string& password, 
			 const uint16_t& personalBest);
		~User() = default;
		User(const User& user);
		User(User&& other)noexcept;

		//operators
		User& operator=(const User& user);
		//User& operator=(User&& user)noexcept;
		
		//validation
		bool ValidateUserEmail() const;
		bool ValidateUserPassword() const;

		//getter
		std::string GetEmail() const;
		std::string GetUsername() const;
		std::string GetPassword() const;
		uint16_t GetPersonalBest() const;

		//setter
		void SetEmail(const std::string& email);
		void SetUsername(const std::string& username);
		void SetPassword(const std::string& password);
		void SetPersonalBest(const uint16_t& personalBest);


		//friend std::ostream& operator<<(std::ostream& ostream, const User& user); //trebe facuta virtuala 
	private:
		std::string m_username;
		std::string m_email;
		std::string m_password;
		uint16_t m_personalBest;
	};
}