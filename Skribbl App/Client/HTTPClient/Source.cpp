#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>

#include <cpr/cpr.h>
#include <crow.h>

// Cerinte client:
// 1. Se vor afisa toate produsele
// 2. Se citesc de la tastatura id produs si cantitatea si se vor adauga in cos (prin 2 modalitati)
// 3. Se afiseaza cosul de cumparaturi si se afiseaza pretul total


int  main()
{
    std::cout << "I installed cpr. Now, my server is the limit!:(\n";
	std::string email;
	std::string username;
	std::string pass;
	std::cin >> email >> username >> pass;

    auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Payload{
			{ "email", email },
			{ "username", username },
			{ "password", pass}
	}
	);
    return 0;
}
