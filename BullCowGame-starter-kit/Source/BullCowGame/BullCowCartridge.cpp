// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic number removal
    PrintLine(TEXT("Press enter to continue..."));
    
    SetupGame();//Setting up Game

    // Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();

    // Checking player guess
    
    if (HiddenWord == Input)
    {
        PrintLine(TEXT("You have Won! :)"));
    }
    else
    {
        if (HiddenWord.Len() != Input.Len())
        {
            PrintLine(TEXT("The hidden word is 4 characters long, try again!")); // Magic number
        }

        PrintLine(TEXT("You have Lost! :("));
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
    HiddenWord = TEXT("cake");
    Lives = 4;
}