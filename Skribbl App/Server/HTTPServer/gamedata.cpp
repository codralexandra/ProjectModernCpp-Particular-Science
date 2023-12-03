#include "gamedata.h"

void populateStorage(Storage& storage)
{
	std::ifstream in("Words.input");
	std::string word, dif;
	std::vector<Word2> cuvinte;
	while (!in.eof())
	{
		in >> word >> dif;
		Word2 w{ -1,word,dif };
		cuvinte.push_back(w);
	}
	storage.insert_range(cuvinte.begin(), cuvinte.end());
	
}
