//test main for pull, modify as needed
#include <iostream>
#include <vector>
import player;
import user;

void Score_Player_Guessing(Scribble::Player& p,int timp)
{
	if (timp == 60)
	{
		p.UpdateScore(p.GetPersonalScore() - 50);
	}
	else if (timp < 30)
	{
		p.UpdateScore(p.GetPersonalScore() + 100);
	}
	else
	{
		int s = (60 - timp) * 100 / 30;
		p.UpdateScore(p.GetPersonalScore() + s);
	}
}

int main() {

	const std::string& aux = "lala@lala";

	Scribble::User u;
	//(aux, "123456789a", { {123,"primulJoc"},{145,"DoiJoc"},{287,"TreiJoc"} }, 287);
	u.SetEmail("lala@lala.com");
	u.SetPassword("aA123456");
	std::queue<std::pair<uint16_t, std::string>>coada;
	coada.push({ 123,"1JOC" });
	coada.push({ 145,"2JOC" });
	coada.push({ 287,"3JOC" });
	u.SetGameHistory(coada);
	u.SetPersonalBest(287);
	u.AddGameToGameHistory({ 305,"4Joc" });
	std::cout << u;

	if (u.validateUserEmail() == true)
	{
		std::cout << "Email ok\n";
	}
	if (u.validateUserPassword() == true)
	{
		std::cout << "Password ok\n";
	}

	return 0;
}