module user;
using namespace Scribble;
import <regex>;


User::User() : m_email(""), m_password(""), m_personalBest(0), m_username("")
{
	//empty
}

Scribble::User::User(const std::string& email, const std::string& username, const std::string& password
	, const uint16_t& personalBest ) :
	m_email(email), m_username(username), m_password(password), m_personalBest(personalBest) 
{
	//empty
}


User& User::operator=(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
	return *this;
}

User& User::operator=(User && user) noexcept
{
	if (this != &user) 
	{
		// Clear the existing data
		m_username.clear();
		m_password.clear();
		m_personalBest = 0;

		// Move data from 'user' to 'this'
		m_username = std::move(user.m_username);
		m_email = std::move(user.m_email);
		m_password = std::move(user.m_password);
		m_personalBest = user.m_personalBest;

		// Clear 'user'
		user.m_email.clear();
		user.m_password.clear();
		user.m_personalBest = 0;
		user.m_username.clear();
	}
	return *this;
}

User::User(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
}

Scribble::User::User(User&& other) noexcept:m_email(other.m_email), m_username(other.m_username), m_password(other.m_password), m_personalBest(other.m_personalBest)
{
	other.m_email.clear();
	other.m_password.clear();
	other.m_personalBest = 0;
}

bool User::ValidateUserEmail() const
{
	std::cout << "Validare Email apelata\n";
	bool emailValid;
	emailValid = std::regex_match(GetEmail(), std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));
	if (!emailValid) {
		std::cout << "The email given is not correct.";
		return false;
	}
	return true;
}

bool User::ValidateUserPassword() const
{
	std::cout << "Validare Parola apelata\n";
	bool allValid = std::regex_match(GetPassword(), std::regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$)"));
	if (!allValid) {
		std::cout << "The password doesn't meet all the requirements.";
		return false;
	}
	return true;
}


std::string User::GetEmail() const
{
	return m_email;
}

std::string Scribble::User::GetUsername() const
{
	return m_username;
}

std::string User::GetPassword() const
{
	return m_password;
}

uint16_t User::GetPersonalBest() const
{
	return m_personalBest;
}

void User::SetEmail(const std::string& email)
{
	m_email = email;
}

void User::SetUsername(const std::string& username)
{
	m_username = username;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

void User::SetPersonalBest(const uint16_t& personalBest)
{
	m_personalBest = personalBest;
}


//std::ostream& Scribble::operator<<(std::ostream& ostream, const User& user)
//{
//	std::queue<std::pair<uint16_t, std::string>> copyGameHistory = user.m_gameHistory;
//	ostream << "Email: " << user.m_email << "\n"
//		<< "Password: " << user.m_password << "\n"
//		<< "Game history: \n";
//	while (!copyGameHistory.empty())
//	{
//		ostream << copyGameHistory.front().first << " " << copyGameHistory.front().second << "\n";
//		copyGameHistory.pop();
//	}
//	ostream << "Personal best: " << user.m_personalBest << "\n";
//	return ostream;
//}