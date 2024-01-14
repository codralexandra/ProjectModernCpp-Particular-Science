#pragma once
#include <string>
namespace Scribble
{
	 class Statistic
	{
	public:
		//constructors and destructor
		Statistic();
		Statistic(const std::string& username, uint16_t& score);
		Statistic(const Statistic& other);
		Statistic(Statistic&& other) noexcept;
		~Statistic() = default;

		//operators
		Statistic& operator=(const Statistic& other);
		Statistic& operator=(Statistic&& other)noexcept;
		//setter
		void SetUsername(const std::string& username);
		void SetScore(uint16_t& score);
		void SetId(uint16_t id);

		//getter
		std::string GetUsername() const;
		uint16_t GetScore()const;
		uint16_t GetId()const;

	private:
		std::string m_username;
		uint16_t m_score;
		uint16_t m_id;


	};
}
