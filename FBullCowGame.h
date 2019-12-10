#pragma once
#include <string>


/*
This is the header of the class FBullCowGame.
Here are the declarations of the class's attributes

declaration of the class's structure, could be written in the class itself
*/

//redeclaration to be like unreal
using FString = std::string;
using int32 = int;


struct FBullCowCount {
	int Bulls = 0;
	int Cows = 0;
};

enum class EWordCheck {
	Invalid_Status,
	OK,
	NOT_LOWERCASE,
	NOT_ISOGRAM,
	TOO_SHORT,
	TOO_LONG
};



class FBullCowGame {

//methods of the class
public:

	FBullCowGame();    //constructor declaration

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	FString GetHiddenWord() const;
	bool IsGameWon()const;
	EWordCheck CheckGuessValidity(FString)const;  

	
	void Reset();
	FBullCowCount SubmitValidGuess(FString);


//attributes of the class
private:

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

};

