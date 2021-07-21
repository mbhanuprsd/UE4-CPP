#include <iostream> // Preprocessor directive <Header file>
#include <ctime>
// add /EHsc for warning free compilation

void PrintIntroduction(int Difficulty)
{
    //Print welcome message
    std::cout << "\nYou are a software developer going through the forest for a trek...";
    std::cout << "\nOn the side of path you find a Level " << Difficulty << " silver colored suitcase with digital lock on it!";
}

bool PlayGame(int Difficulty)
{
    PrintIntroduction(Difficulty);

    // Declare three number code
    const int PinA = rand() % Difficulty + Difficulty;
    const int PinB = rand() % Difficulty + Difficulty;
    const int PinC = rand() % Difficulty + Difficulty;

    const int PinSum = PinA + PinB + PinC;
    const int PinProduct = PinA * PinB * PinC;

    // Print PinSum and Pin Product to the terminal
    std::cout << "\n\nThe lock  has 3 digit pin";
    std::cout << "\nThe digits in the pin add up to " << PinSum;
    std::cout << "\nAnd their product is " << PinProduct;

    // Save the players guess
    int GuessA, GuessB, GuessC;
    std::cout << "\n\nGuess the pin : ";
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Check whether the player guess is correct or not
    if (GuessSum == PinSum && GuessProduct == PinProduct)
    {
        std::cout << "\nYou opened the suitcase.";
        std::cout << "\nHooray! You got a piece of map. Find the next.\n";
        return true;
    }
    else
    {
        std::cout << "\nWrong Pin! Suitcase is self destructing! 3... 2... 1... Booom!\nRetry Again!\n";
        return false;
    }
}

int main()
{
    srand(time(NULL)); // Shuffles random seed

    int CurrentLevel = 1;
    const int MaxLevel = 5;

    while (CurrentLevel <= MaxLevel) // Loop game until all levels are completed
    {
        bool bLevelComplete = PlayGame(CurrentLevel);
        std::cin.clear();  // Clears any errors
        std::cin.ignore(); // Discards the buffer

        if (bLevelComplete)
        {
            ++CurrentLevel;
        }
    }

    std::cout << "Congratulations!! You have successfully unlocked all cases.";
    return 0;
}