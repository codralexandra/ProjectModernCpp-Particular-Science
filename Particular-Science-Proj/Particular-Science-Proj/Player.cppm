module;
export module player;

#include "User.h"
import<cstdint>;
import<chrono>;


namespace Scribble
{
	export class Player : public User
	{
	public:

		Player();
		Player(bool isDrawing);
		Player(const Player& player);

		Player(bool hasGuessed, bool hasDrawn, uint16_t timeGuessed, std::string nickname,
			bool isDrawing, bool hasTopScore, int16_t personalScore, uint16_t position);


		void SetNickname(std::string nickname);
		void SetIsDrawing(bool isDrawing);
		void SetHasGuessed(bool hasGuessed);
		void SetHasDrawn(bool hasDrawn);
		void UpdateScore(int16_t newscore);
		void UpdatePosition(uint16_t position);


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