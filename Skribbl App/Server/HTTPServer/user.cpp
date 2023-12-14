module user;
using Scribble::User;
import <regex>;

User::User() : m_email(""), m_password(""), m_personalBest(0), m_username("")
{

}

User::User(const std::string& email, const std::string& username, const std::string& password, 
	 const uint16_t& personalBest) :
	m_email(email),m_username(username), m_password(password),  m_personalBest(personalBest)
{

}

User& User::operator=(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	//m_gameHistory = user.m_gameHistory;
	m_personalBest = user.m_personalBest;
	return *this;
}

User::User(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	//m_gameHistory = user.m_gameHistory;
	m_personalBest = user.m_personalBest;
}

bool User::validateUserEmail()
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

bool User::validateUserPassword()
{
	std::cout << "Validare Parola apelata\n";
	bool allValid = std::regex_match(GetPassword(), std::regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$)"));
	if (!allValid) {
		std::cout << "The password doesn't meet all the requirements.";
		return false;
	}
	return true;
}

User::~User()
{
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

//std::queue<std::pair<uint16_t, std::string>> User::GetGameHistory() const
//{
//	return m_gameHistory;
//}

uint16_t User::GetPersonalBest() const
{
	return m_personalBest;
}

void User::SetEmail(const std::string& email)
{
	m_email = email;
}

void User::SetUsername(std::string username)
{
	m_username = username;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

//void User::SetGameHistory(const std::queue<std::pair<uint16_t, std::string>>& gameHistory)
//{
//	m_gameHistory = gameHistory;
//}

void User::SetPersonalBest(const uint16_t& personalBest)
{
	m_personalBest = personalBest;
}

//void User::AddGameToGameHistory(std::pair<uint16_t, std::string> game)
//{
//	std::cout << "ADD Game to History apelata\n";
//	if (m_gameHistory.size() >= 5)
//	{
//		m_gameHistory.pop();
//		m_gameHistory.push(game);
//	}
//	else
//	{
//		m_gameHistory.push(game);
//	}
//}

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