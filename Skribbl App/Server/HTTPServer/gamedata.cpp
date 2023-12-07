#include "gamedata.h"

void populateStorage(Storage& storage)
{
	std::ifstream in("Words.input");
	std::string word, dif;
	std::vector<Word> cuvinte;
	while (!in.eof())
	{
		uint16_t id = -1;
		in >> word >> dif;
		Word w{id, word,dif };
		cuvinte.push_back(w);
	}


	storage.insert_range(cuvinte.begin(), cuvinte.end());
	//inserare pt word cum inserez user 

}
