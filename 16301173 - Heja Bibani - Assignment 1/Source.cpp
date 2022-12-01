#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <iterator>
#include <ctime>


using namespace std;

struct positionsAvailable
{
public:
	int rowAv;
	int colAv;

	void operator =(positionsAvailable p)
	{
		rowAv = p.rowAv;
		colAv = p.colAv;
	}
};

struct positionsTop
{
	public:
		int blockNumber;
		int rowTop;
		int colTop;

		void operator =(positionsTop p)
		{
			blockNumber = p.blockNumber;
			rowTop = p.rowTop;
			colTop = p.colTop;
		}
};


#include "Goal.h"
#include "State.h"
#include "Action.h"
#include "Plan.h"
#include "Game.h"

int main()
{
	srand(time(0));
	Game game;
	game.startGame();

	return 0;
}
