//Main program

#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#include "Cell.h"
#include "TicTacToe.h"
#include "HumanPlayer.h"
#include "BestFirstPlayer.h"
#include "Game.h"

using namespace std;

int main() {
	srand(time(0));

	Game game;

	game.play();

	return 0;
}
