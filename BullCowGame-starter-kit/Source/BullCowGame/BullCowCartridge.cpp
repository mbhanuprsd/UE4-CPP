// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cow game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic number removal
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("cake");  // Move outside this function
    if (HiddenWord == Input)
    {
        PrintLine(TEXT("You have Won! :)"));
    }
    else
    {
        PrintLine(TEXT("You have Lost! :("));
    }
}