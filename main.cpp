/*
This is the main file which controls all the user input
To see the logic of the FBullCowGame go to the respective class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//redeclaration to be like unreal
using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


//declaretion of my class
FBullCowGame BCGame;


int main() {

	PrintIntro();

	do {

		PlayGame();


	} while (AskToPlayAgain()); //TODO checking why error

	return 0;
}


//print introduction
void PrintIntro()                               //TODO ASCII art
{

	std::cout << "Welcome to Bull & Cows!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram to hack into the pipboy you have found?\n";
	std::cout << BCGame.GetHiddenWord();

	return;
}

//start the game by making a new object of the class
void PlayGame()
{
	FBullCowGame();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BCCount.Bulls;
		std::cout << " | Cows = " << BCCount.Cows << std::endl;
	}


	PrintGameSummary();


	return;
}

//receive the input
FText GetValidGuess()
{
	EWordCheck WordStatus = EWordCheck::Invalid_Status;
	FText Guess;

	do {

		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "\n\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Make a guess: ";
		std::getline(std::cin, Guess);

		//handling of different errors
		WordStatus = BCGame.CheckGuessValidity(Guess);
		switch (WordStatus) {

		case EWordCheck::NOT_ISOGRAM:
			std::cout << "\nPlease enter an isogram, a word with all different letters.\n";
			break;
		case EWordCheck::NOT_LOWERCASE:
			std::cout << "\nPlease enter only lowercase letters.\n";
			break;

		case EWordCheck::TOO_LONG:
			std::cout << "\nPlease enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;

		case EWordCheck::TOO_SHORT:
			std::cout << "\nPlease enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;

		default:
			return Guess;
			break;

		}



	} while (WordStatus != EWordCheck::OK);   //loop until the guess is valid
}

bool AskToPlayAgain()   //TODO perche cazzo non funziona
{
	FText Response;

	std::cout << "\nDo you want another round of fun? Yes or No?";
	std::cin >> Response;

	return (Response[0] == 'y' || Response[0] == 'Y');
}

//print results
void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "\nYOU WON! WHAT A PRO!\n";
	}
	else {
		std::cout << "\nYOU LOSE! BETTER LUCK NEXT TIME!\n";
	}

}