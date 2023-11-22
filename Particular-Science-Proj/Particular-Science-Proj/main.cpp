//test main for pull, modify as needed
#include <iostream>
#include <vector>
import player;
import user;
import game;
//#include "Round.h"
#include "SubRound.h"

void Score_Player_Guessing(Scribble::Player& p,int timp)
{
	if (timp == 60)
	{
		p.SetScore(p.GetPersonalScore() - 50);
	}
	else if (timp < 30)
	{
		p.SetScore(p.GetPersonalScore() + 100);
	}
	else
	{
		int s = (60 - timp) * 100 / 30;
		p.SetScore(p.GetPersonalScore() + s);
	}
}

int main() {

	//const std::string& aux = "lala@lala";

	/*Scribble::User u;
	u.SetEmail("lala@lala.com");
	u.SetPassword("aA123456");
	std::queue<std::pair<uint16_t, std::string>>coada;
	coada.push({ 123,"1JOC" });
	coada.push({ 145,"2JOC" });
	coada.push({ 287,"3JOC" });
	u.SetGameHistory(coada);
	u.SetPersonalBest(287);
	u.AddGameToGameHistory({ 305,"4Joc" });*/
	//std::cout << u;

	//if (u.validateUserEmail() == true)
	//{
	//	std::cout << "Email ok\n";
	//}
	//if (u.validateUserPassword() == true)
	//{
	//	std::cout << "Password ok\n";
	//}

	Scribble::Player p;
	
	p.SetHasDrawn(true);
	p.SetHasGuessed(false);
	p.SetNickname("blabla");
	p.SetIsDrawing(true);
	p.SetPosition(2);
	p.SetScore(100);
	p.SetHasTopScore(true);
	//std::cout << p;
	//Score_Player_Guessing(p,30);
	//std::cout << std::endl << p;

	Scribble::Player r;

	r.SetHasDrawn(true);
	r.SetHasGuessed(false);
	r.SetNickname("aaaaaaaa");
	r.SetIsDrawing(true);
	r.SetPosition(1);
	r.SetScore(150);
	r.SetHasTopScore(true);

	////if (p > r)
	////{
	////	std::cout << p;
	////}
	////else
	////	std::cout << r;

	Scribble::Game g;
	g.setDate("12-12-2022");
	g.setPlayers({ p,r });
	g.setWords({ "house","table" });
	
	std::cout << g.getDate() << std::endl;
	for (int i = 0; i < g.getPlayers().size(); i++)
	{
		std::cout << g.getPlayers()[i];
	}
	for (auto word : g.getWords())
	{
		std::cout << word<<" ";
	}
	g.Start_Game();

	//Round q;
	//std::cout<< q.GetDrawer();
	//q.StartRound(g);

	//SubRound sr;
	//sr.StartSubRound();
	
	return 0;
}