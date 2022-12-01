/*
 * Game.h
 *
 *  Created on: 22 Mar. 2019
 *      Author: dongmo
 */

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	void play() {
		ticTacToe board;
		board.displayBoard();

		HumanPlayer hplayer('X');
		BestFirstPlayer mplayer('O');

		bool done = false;
		char player = 'X';

		while (!done) {
			int x = -1;
			int y = -1;
			if (player == 'X') {
				hplayer.getMove(board, x, y);
				board.addMove(player, x, y);
				cout << "X makes a move (" << (x + 1) << "," << (y + 1) << ") "
						<< endl;
				board.displayBoard();
				done = checkWin(player, board);
				player = 'O';
			} else {
				mplayer.getMove(board, x, y);
				board.addMove(player, x, y);
				cout << "O makes a move (" << (x + 1) << "," << (y + 1) << ") "
						<< endl;
				board.displayBoard();
				done = checkWin(player, board);
				player = 'X';
			}
		}
	}

	bool checkWin(char playerSymbol, ticTacToe board) {
		char gStatus = board.gameStatus();

		if (gStatus == playerSymbol) {
			cout << "Player " << playerSymbol << " wins!" << endl;
			return true;
		} else if (gStatus == 'D') {
			cout << "This game is a draw!" << endl;
			return true;
		} else if (gStatus != 'C') {
			return true;
		} else
			return false;
	}
};

#endif /* GAME_H_ */
