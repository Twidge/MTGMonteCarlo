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

using namespace std;

const unsigned int G_NUMBER_OF_TRIALS = 1000;
const unsigned int G_TURNS_TO_CHECK = 3;
const bool G_ON_PLAY = true;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	unsigned int t_mana[G_MANA_TYPES] {0, 1, 0, 0, 0, 1, 0};

	const Card t_cardToCheck = Card("Fleecemane Lion", Creature, Mana(t_mana));

	float t_successfulTrials = 0;

	Player t_simPlayer = Player();
	t_simPlayer.ConstructDeck("decklist.txt");
	SimulationController t_simController = SimulationController(&t_simPlayer);

	for (unsigned int l_trial = 0; l_trial < G_NUMBER_OF_TRIALS; l_trial++)
	{
		if (t_simController.RunSimulation(t_cardToCheck, G_TURNS_TO_CHECK, G_ON_PLAY))
		{
			t_successfulTrials++;
		}

		if (l_trial % 100 == 0 && l_trial != 0)
		{
			std::cout << "Trial " << l_trial << " done.\n";
		}
	}

	std::cout << "Number of trials: " << G_NUMBER_OF_TRIALS << ".\n";
	std::cout << "Successful trials: " << t_successfulTrials << ".\n";

	std::cin.get();

	return 0;
}