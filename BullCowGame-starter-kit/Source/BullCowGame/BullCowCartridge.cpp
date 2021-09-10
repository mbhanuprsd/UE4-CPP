// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking player guess
    {
       ProcessGuess(Input);
    }

    // Check if isogram
    // Check is right number of characters

    // Remove life

    // Are the lives > 0
    // If true, guess again
    // Show lives left
    // If false, show gameover and hiddenword?
    // Prompt to play again, Press enter to play again
    // Check user Input

    // PlayAgain or Quit
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow game!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!\nYou have %i lives"), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type in your guess and\npress enter to continue...")); // Prompt player for guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
     if (HiddenWord == Guess)
        {
            PrintLine(TEXT("You have Won! :)"));
            EndGame();
        }
        else
        {
            PrintLine(TEXT("You have lost a life!"));
            PrintLine(TEXT("You have %i lives."), --Lives);
            if (Lives > 0)
            {
                if (HiddenWord.Len() != Guess.Len())
                {
                    PrintLine(TEXT("Word is %i characters long!"), HiddenWord.Len());
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
        }
}