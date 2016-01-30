#include <iostream>
#include <cstdlib>	// for rand() and srand()
#include <ctime>	// for time()


// Generate a random number between max and min(inclusive)
// Assumes srand() has already been called
int getRandomNumber(int min, int max)
{
	// static used for efficiency, so we calculate this value once
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	// evenly distribute random number across our range
	return static_cast<int>(rand() * fraction * (max - min) + min);
}


int getGuess(int count)
{
	std::cout << "Guess #" << count << ": ";
	int guess;
	std::cin >> guess;

	return guess;
}


bool checkAndPrintResult(int number, int guess, int count)
{
	bool hasWon = false;
	
	if (guess > number)
		std::cout << "Your guess is too high." << std::endl;
	else if (guess < number)
		std::cout << "Your guess is too low." << std::endl;
	else
	{
		std::cout << "Congrats! You won!" << std::endl;
		hasWon = true;
	}

	return hasWon;
}


// play a single game of hi-lo
void playHiLo()
{
	// START GAME...
	
	// Game parameters:
	int numberOfTries(5);
	int rangeMax(100);

	// set initial seed value to system clock
	// call this before calling getRandomNumber()
	srand(static_cast<unsigned int>(time(0)));

	// get a random number between 1 and 100 (both inclusive)
	int number = getRandomNumber(1, 100);

	// Initial parameters before playing game:
	bool hasWon(false);
	int count(0);
	int guess(0);

	do
	{
		// Increments count as soon as loop is entered
		++count;

		guess = getGuess(count);
		hasWon = checkAndPrintResult(number, guess, count);
		
		// if won, exit loop
		if (hasWon)
			break;
	}
	while (!hasWon && count <= 5);

	// ...END OF GAME
}


char askAgain()
{
	std::cout << "Would you like to play again (y/n): ";
	char choice;
	std::cin >> choice;

	return choice;
}


bool playAgain()
{
	char userChoice = askAgain();

	if (userChoice == 'y')
		return true;
	else if (userChoice == 'n')
		return false;
	else
		askAgain();
}


int main()
{
	std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 5 tries to guess what it is.\n";

	// plays a single game of hi-lo
	playHiLo();

	bool willPlayAgain = playAgain();

	while (willPlayAgain)
	{
		playHiLo();
	}

	return 0;
}
