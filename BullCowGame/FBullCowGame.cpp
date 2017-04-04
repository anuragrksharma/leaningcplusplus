#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

// This would be similar to impl(s) in JAVA.

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::AllUserInputStrings()
{
	return;
}

EGuessStatus FBullCowGame::CheckCurrentUserInput(FString input) const
{
	//TODO Add check, return error / success

	if (input.length() != HiddenWord.length()) {
		return EGuessStatus::INVALID_LENGTH;	
	}
	else if (!IsLowerCase(input)) {
		return EGuessStatus::NOT_ALL_LOWER_CASE;
	}
	else if (!IsIsogram(input)) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon == true;
}

bool FBullCowGame::IsIsogram(FString User_Input) const
{
	TMap<char, bool> LetterSeen; // instantiate map

	for (auto Letter : User_Input)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString User_Input) const
{
	for (auto Letter : User_Input)
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return HiddenWord.length();
}

// Receives valid guess, increments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the current try
	MyCurrentTry++;

	FBullCowCount CurrentTryBullCowCount;
	const int32 WORD_LENGTH = HiddenWord.length(); //assuming guess is valid.
	for (int32 i = 0; i < WORD_LENGTH; i++) {
		for (int32 j = 0; j < WORD_LENGTH; j++) {
			if (Guess[i] == HiddenWord[j] && i == j) {
				CurrentTryBullCowCount.Bulls++;
			}
			else if (Guess[i] == HiddenWord[j] && i != j) {
				CurrentTryBullCowCount.Cows++;
			}
		}
	}

	if (CurrentTryBullCowCount.Bulls == WORD_LENGTH && CurrentTryBullCowCount.Cows == 0)
	{
		bGameWon = true;
	}
	return CurrentTryBullCowCount;
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyMaxTries = 8;
	HiddenWord = "planet";
	return;
}
