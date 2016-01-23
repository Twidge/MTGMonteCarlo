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

const unsigned int G_NUMBER_OF_TRIALS = 100000;
const unsigned int G_TURNS_TO_CHECK = 4;
const bool G_ON_PLAY = true;

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

	float t_successfulTrials = 0;

	Player t_simPlayer = Player();
	t_simPlayer.ConstructDeck("decklist.txt");
	SimulationController t_simController = SimulationController(&t_simPlayer);

	for (unsigned int l_trial = 0; l_trial < G_NUMBER_OF_TRIALS; l_trial++)
	{
		if (t_simController.RunAndSimulation(t_cardsToCheck, G_TURNS_TO_CHECK, G_ON_PLAY))
		{
			t_successfulTrials++;
		}

		if (l_trial % 10000 == 0 && l_trial != 0)
		{
			std::cout << "Trial " << l_trial << " done.\n";
		}
	}

	std::cout << "Number of trials: " << G_NUMBER_OF_TRIALS << ".\n";
	std::cout << "Successful trials: " << t_successfulTrials << ".\n";

	std::cin.get();

	return 0;
}