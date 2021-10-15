// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
// #include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordsPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    // Loads words which are isograms to words arary
    FFileHelper::LoadFileToStringArrayWithPredicate(Words, *WordsPath, [](const FString &Word)
                                                    { return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word); });

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking player guess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow game!"));

    HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!\nYou have %i lives"), HiddenWord.Len(), Lives);
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line
    PrintLine(TEXT("Type in your guess and\npress enter to continue...")); // Prompt player for guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPlease press Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (HiddenWord == Guess)
    {
        PrintLine(TEXT("You have Won! :)"));
        EndGame();
        return;
    }

    // Check is right number of characters
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry, Hidden word is %i characters long.\n Guess again"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left."), Lives);
        return;
    }

    // Check if isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("There are repeating letters, guess again!"));
        return;
    }

    // Remove life
    PrintLine(TEXT("You have lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    // Show the player Bulls and Cows
    
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("You have %i lives3 left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word)
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
