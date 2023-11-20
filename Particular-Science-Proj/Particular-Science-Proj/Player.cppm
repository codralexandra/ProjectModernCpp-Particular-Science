module;
export module player;
import user;
import <cstdint>;
import <chrono>;


namespace Scribble
{
	export class Player : public User
	{
	public:

		Player();
		Player(bool isDrawing);
		Player(const Player& player);

		Player(bool hasGuessed, bool hasDrawn, uint16_t timeGuessed, std::string nickname,
			bool isDrawing, bool hasTopScore, int16_t personalScore, uint16_t position, const std::string& email, const std::string& password, 
			const std::queue<std::pair<uint16_t, std::string>> gameHistory, uint16_t personalBest);


		void SetNickname(std::string nickname);
		void SetIsDrawing(bool isDrawing);
		void SetHasGuessed(bool hasGuessed);
		void SetHasDrawn(bool hasDrawn);
		void SetScore(int16_t newscore);
		void SetPosition(uint16_t position);
		void SetHasTopScore(bool topScore);

		std::string GetNickname();
		bool GetIsDrawing();
		int16_t GetPersonalScore();
		bool GetHasTopScore();
		uint16_t GetPosition();
		bool GetHasGuessed();
		bool GetHasDrawn();
		uint16_t GetTimeGuessed();



		Player& operator = (const Player& player);
		bool operator<(const Player& player) const;
		bool operator>(const Player& player) const;

	private:
		bool m_hasGuessed;
		bool m_hasDrawn;
		uint16_t m_timeGuessed;
		std::string m_nickname;
		bool m_isDrawing;
		bool m_hasTopScore;
		int16_t m_personalScore;
		uint16_t m_position;
	};
	export std::ostream& operator<<(std::ostream& os, Player& player);
}