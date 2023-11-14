module;
import <iostream>;
import <vector>;
import "Difficulty.h";
import player;
export module game;

namespace Scribble1
{
	export class Game
	{
	public:
		Game();
		Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date);

		void setPlayers(std::vector<Player> players);
		void setWords(std::vector<std::string> words);
		void setDate(std::string date);

		std::vector<Player> getPlayers();
		std::vector<std::string> getWords();
		std::string getDate();

		void Start_Game();
		void Score_Player_Drawing(Player& p, std::vector<Player>players_guessing);
		void updateHistoryPlayer();
	private:
		std::vector<Player> m_players;
		Difficulty m_difficulty;
		static const uint16_t m_rounds = 4;
		std::vector<std::string> m_words;
		std::string m_date; //regex check or make class
	};

}