//Includes
#include "Tests.h"

//Namespace

//Defines

//Const

//Prototypes

//Functions
bool test::distance(Map* map)
{
	default_random_engine randomEngine((unsigned)time(0));
	Hex* currentHex = nullptr;
	Hex* testHex = nullptr;
	for ( int row = 0 ; row < map->getHeight() ; ++row)
	{
		for ( int column = 0 ; column < map->getWidth() ; ++column)
		{
			currentHex = map->getHex(column, row);
			testHex = map->getHex(column, row);
			assert(currentHex->calculateDistance(testHex) == 0);

			for ( int times = 0 ; times < 10000 ; ++times)
			{
				for ( int deplacements = 0 ; deplacements < times%50 ; ++deplacements)
				{
					if (testHex != 0)
						testHex = testHex->getAdjacentHex((randomEngine() % 2) + times%5);
				}
				if (testHex != 0)
					assert(currentHex->calculateDistance(testHex) == times%50);
				testHex = currentHex;
				
			}
		}
	}
	return true;
}
