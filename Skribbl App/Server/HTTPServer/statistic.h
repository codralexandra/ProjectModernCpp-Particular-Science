
#include <string>
class Statistic
{
public:
	Statistic();
	Statistic(const std::string& username, uint16_t score);
	~Statistic() = default;

	//setter
	void SetUsername(const std::string& username);
	void SetScore(uint16_t score);
	
	//getter
	std::string GetUsername() const;
	uint16_t GetScore()const;

private:
	std::string m_username;
	uint16_t m_score;
	

};

