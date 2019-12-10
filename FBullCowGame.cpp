#pragma once
#include "FBullCowGame.h"
#include <ctime>
#include <time.h>
#include <map>


/*
This is the definition of the attributes of the class.
*/

//redeclaration to be like unreal
#define Tmap std::map
using FString = std::string;
using int32 = int;


//constructor default
FBullCowGame::FBullCowGame()
{
	Reset();
}

//getters, they are const so they will never change the value they are used to return

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }  //debug purposes
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	Tmap<int32, int32> WordLenghtToMaxTries{ {GetHiddenWordLenght(), (GetHiddenWordLenght() * 2)} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}





void FBullCowGame::Reset()                //called inside the constructor
{
	
	MyCurrentTry = 1;
	const int32 WordList = 10;
	
	FString HiddenWords[WordList] = {"man", "star", "world", "alien", "woman", "matrix", "planet", "racing", "mistake", "ubermansch"};  //ALL ISOGRAMS
	
	srand(time(0));
	MyHiddenWord = HiddenWords[rand() % WordList];
	bGameWon = false;

	return;
}


EWordCheck FBullCowGame::CheckGuessValidity(FString Guess) const      
{

	//TODO searching about implicit dependencies and implementing multi error messages
	if (!IsLowerCase(Guess)) {
		return EWordCheck::NOT_LOWERCASE;
	}
	
	else  if (!IsIsogram(Guess)) {
		return EWordCheck::NOT_ISOGRAM;
	}

	else if ((int)Guess.length() < (int)GetHiddenWordLenght()) {
	return EWordCheck::TOO_SHORT;
	}

	else if ((int)Guess.length() > (int)GetHiddenWordLenght()) {
	return EWordCheck::TOO_LONG;
	}
		
	else {
		return EWordCheck::OK;
	}
}



FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	
	MyCurrentTry++;
	
	FBullCowCount BCCount;

	int HiddenWordLenght = MyHiddenWord.length();

	for (int32 GChar = 0; GChar < HiddenWordLenght; GChar++) {
		for (int32 HDChar = 0; HDChar < HiddenWordLenght; HDChar++) {

			if (Guess[GChar] == MyHiddenWord[HDChar]) {   
				if (GChar == HDChar) {
					BCCount.Bulls++;
				}
				else {
					BCCount.Cows++;
				}
			}
		}
	}
	//check if we won to modify the variables so we can than call in the main an if with the gamewon function
	if (BCCount.Bulls == GetHiddenWordLenght()) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}

	return BCCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	
	//consider cases of 0 and 1 letters --> isograms
	if (Guess.length() < 2) { return true; }

	Tmap <char, bool> LetterSeen;

	//for every char in the guess
	//auto automatically deduces the type of variable
	for (auto Letter : Guess) {

		Letter = tolower(Letter);

		//if letter is already seen in the map, not an isogram
		if (LetterSeen[Letter]) {
			return false;
	}   //otherwise puts it in the map
		else {
			LetterSeen[Letter] = true;
		}
			
	}
	return true; 
}

bool FBullCowGame::IsLowerCase(FString Guess) const{

	if (Guess.length() < 1) { return true; }

	//for each char if one is not lowercase return false
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}


