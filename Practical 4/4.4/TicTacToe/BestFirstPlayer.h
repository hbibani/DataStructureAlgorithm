/*
 * BestFirstPlayer.h
 *
 *  Created on: 27 Mar. 2019
 *      Author: dongmo
 */

#ifndef BESTFIRSTPLAYER_H_
#define BESTFIRSTPLAYER_H_

class BestFirstPlayer {
	char playerSymbol;
public:
	BestFirstPlayer(char ps) {
		playerSymbol = ps;
	}

	void getMove(ticTacToe board, int& x, int& y) {
		if (board.isFull())
			return;

		priority_queue<Cell> moves;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ticTacToe tempBoard(board);
				if (tempBoard.isValidMove(i, j)) {
					tempBoard.addMove(playerSymbol, i, j);
					Cell c(i, j, tempBoard.heuristics(playerSymbol));
					moves.push(c);
				}
			}
		}

		if (moves.size() > 0) {
			x = moves.top().x;
			y = moves.top().y;
		} else {
			cout << "Can't find a new replacement" << endl;
		}

		cout << "Heuristic = " << moves.top().heuristic << " at ("
				<< (x + 1) << "," << (y + 1) << ")" << endl;
	}
};

#endif /* BESTFIRSTPLAYER_H_ */
