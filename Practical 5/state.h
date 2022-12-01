/*
 * state.h
 *
 *  Created on: 29/02/2020
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

const int BOARDSIZE = 3;
const int NUMBER_OF_BLOCKS = 6;

class State {
private:
	int grid[BOARDSIZE][BOARDSIZE];
public:

	State() {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				grid[i][j] = rand() % 2;
	}

	bool operator==(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.grid[i][j] != grid[i][j])
					return false;
		return true;
	}

	void printBoard();
};

void State::printBoard() {
	cout << endl;

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			cout << " " << grid[BOARDSIZE - i - 1][j] << " ";
		}
		cout << endl;
	}
}

#endif /* BOARD_H_ */
