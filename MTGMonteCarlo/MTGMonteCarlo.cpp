// MTGMonteCarlo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimulationController.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <future>

using namespace std;

const unsigned int G_NUMBER_OF_TRIALS = 1000000;
const unsigned int G_TURNS_TO_CHECK = 4;
const unsigned int G_SIMULTANEOUS_THREADS = 4;
const bool G_ON_PLAY = true;

/*
	IMPORTANT NOTE: When run through Visual Studio, adding more threads greatly slows the runtime of the application.
	When run from the executable or in the performance/diagnostic window, the application speeds up as expected.

	I'm not sure why this is.
*/

int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	unsigned int t_mana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};
	unsigned int t_secondMana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};
	unsigned int t_thirdMana[G_MANA_TYPES] {0, 0, 0, 0, 0, 0, 0};

	const Card t_cardToCheck = Card("Jeskai Ascendancy", Enchantment, Mana(t_mana));
	const Card t_secondCardToCheck = Card("Rattleclaw Mystic", Creature, Mana(t_secondMana));
	const Card t_thirdCardToCheck = Card("Expedite", Instant, Mana(t_thirdMana));

	std::vector<Card> t_cardsToCheck{ t_cardToCheck, t_secondCardToCheck, t_thirdCardToCheck };

	Player t_playerOne = Player();
	Player t_playerTwo = Player();
	t_playerOne.ConstructDeck("decklist.txt");
	t_playerTwo.ConstructDeck("decklist.txt");
	SimulationController t_simOne = SimulationController(&t_playerOne);
	SimulationController t_simTwo = SimulationController(&t_playerTwo);
	
	/*
	unsigned int t_successfulTrials = 0;

	for (unsigned int l_trial = 0; l_trial < G_NUMBER_OF_TRIALS; l_trial++)
	{
		if (t_simOne.RunAndSimulation(t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY))
		{
			t_successfulTrials++;
		}

		if (l_trial % (G_NUMBER_OF_TRIALS / 10) == 0 && l_trial != 0)
		{
			std::cout << "Trial " << l_trial << " done.\n";
		}
	}
	*/

	/*
	std::future<unsigned int> t_futureOne = std::async(std::launch::async, &SimulationController::RunAndSimulationLoop,
		&t_simOne, t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY, G_NUMBER_OF_TRIALS / 2);

	std::future<unsigned int> t_futureTwo = std::async(std::launch::async, &SimulationController::RunAndSimulationLoop,
		&t_simTwo, t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY, G_NUMBER_OF_TRIALS / 2);
	*/

	std::vector<Player> t_simPlayers = std::vector<Player>(G_SIMULTANEOUS_THREADS);
	std::vector<SimulationController> t_simControllers = std::vector<SimulationController>(G_SIMULTANEOUS_THREADS);
	std::vector<std::future<unsigned int>> t_trialResults = std::vector<std::future<unsigned int>>(G_SIMULTANEOUS_THREADS);

	for (unsigned int l_testInstance = 0; l_testInstance < G_SIMULTANEOUS_THREADS; l_testInstance++)
	{
		t_simPlayers[l_testInstance] = Player();
		t_simPlayers[l_testInstance].ConstructDeck("decklist.txt");
		t_simControllers[l_testInstance] = SimulationController(&t_simPlayers[l_testInstance]);

		t_trialResults[l_testInstance] = std::async(&SimulationController::RunAndSimulationLoop,
			&t_simControllers[l_testInstance], t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY, G_NUMBER_OF_TRIALS / 2);
	}

	unsigned int t_successfulTrials = 0;

	for (unsigned int l_testInstance = 0; l_testInstance < G_SIMULTANEOUS_THREADS; l_testInstance++)
	{
		t_successfulTrials += t_trialResults[l_testInstance].get();
	}

	// unsigned int t_successfulTrials = t_futureOne.get() + t_futureTwo.get();

	std::cout << "Number of trials: " << G_NUMBER_OF_TRIALS << ".\n";
	std::cout << "Successful trials: " << t_successfulTrials << ".\n";

	return 0;
}