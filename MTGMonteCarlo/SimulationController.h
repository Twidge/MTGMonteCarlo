#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

class Card;
class Player;

class SimulationController
{
public :

	// CONSTRUCTORS

	SimulationController();
	SimulationController(SimulationController const&);
	SimulationController(const Player*);

	// DESTRUCTOR

	~SimulationController();

	// OPERATOR OVERLOADS

	void operator= (SimulationController const&);

	// METHODS

	bool RunSimulation(Card const&, unsigned int, bool);

private :

	Player* m_tester;
};

#endif