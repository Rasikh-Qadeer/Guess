#include "stdafx.h"  // Standard header

#include <iostream> // For our input/outputs
#include <stdlib.h> // Standard library for utilities
#include <time.h> // To seed random index
#include <Vector> // To handle efficient tables
#include <string> // To get string functions
#include <algorithm> // To get useful algorithms for instance conversion of strings to lower case for comparisons
#include <Windows.h> // Colorizing purposes

#include "Utils.h" // Our own Utilities

// Tables
std::vector<std::string> tbl_Countries = {
	"pa-kist-an",
	"fi-nla-nd",
	"in-dia",
	"bal-ochi-sta-n",
	"-nepa-l"
};

// Vars
int RND_CountryIndex = -1;
std::string UserInput = "";
std::string lower_UserInput;

int main()
{
	MAIN:
	// Environment setup
	bool random_choices = true;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(static_cast<unsigned int>(time(NULL)));
	system("cls");
	//
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "=====================================" << std::endl;
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Welcome to the country guessing game!" << std::endl;
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "== How to Play ==" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "A random country name will be given,\nthe objective is to guess what country it is and write its name completely,\na few hints are also provided to help guess!" << std::endl;
	std::cout << "You may exit any time by writing 'exit'" << std::endl;
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "=====================================" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	system("pause");
	std::cout << "Let the guessing begin!" << std::endl;
	//
	GAME:
	RND_CountryIndex = random_choices ? GetRandomNumber(0, tbl_Countries.size()-1) : RND_CountryIndex+1;
	if(RND_CountryIndex == tbl_Countries.size()) {
		RND_CountryIndex = 0;
	}
	std::string CountryToGuess = tbl_Countries[RND_CountryIndex];
	std::string hidden_CountryToGuess = "";
	std::string clean_CountryName = "";

	bool Hint = false;
	for(char ch : CountryToGuess) {
		if(ch == '-') {
			Hint = true;
			continue;
		} else {
			clean_CountryName += ch;
		}

		if(Hint) {
			hidden_CountryToGuess += ch;
			Hint = false;
		} else {
			hidden_CountryToGuess += "*";
		}
	}
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << hidden_CountryToGuess.c_str() << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	GUESS:
	while(true) {
		std::getline(std::cin, UserInput);
		//
		lower_UserInput = "";
		std::transform(UserInput.begin(), UserInput.end(), std::back_inserter(lower_UserInput), ::tolower);
		//
		if(lower_UserInput == clean_CountryName) {
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "Correct!!" << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			goto GAME;
		} else if(lower_UserInput == "exit") {
			goto END;
		} else {
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "Incorrect! Try guessing again..." << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}

	END:
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "Thank you for playing!" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	system("pause");
    return 0;
}