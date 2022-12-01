#ifndef State_h
#define State_h

class State
{
private:
	int rows;							 //size of the board					 						 // number of steps for time complexity
	vector< int > numbers;				 //vector to hold numbers to place into box randomly [we pick a random number in the position of the vector]

public:
	int totalCount;
	int** board;
	~State();
	void destroyBoard();

	int getRows() const
	{
		return rows;
	}

	State(int r)
	{
		//takes rows; and rows will act as column, since the board is square. 
		rows = r;
		totalCount = (rows * rows) - rows;
		board = new int* [rows];
		

		for (int i = 0; i < rows; i++)
		{
			board[i] = new int[rows];
		}

		for (int i = 1; i <= totalCount; i++)
		{
			numbers.push_back(i); //create the number of values inside the vector to pick randomly - it will be between 1 and 2(n) - for 3 it will be between 1 and 6
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				board[i][j] = 0; //initialize board to 0's
			}
		}
	}

	
	void setBoard(int r)
	{
		//takes rows; and rows will act as column, since the board is square. 
		rows = r;
		totalCount = (rows * rows) - rows;
		board = new int* [rows];
	

		for (int i = 0; i < rows; i++)
		{
			board[i] = new int[rows];
		}

		for (int i = 1; i <= totalCount; i++)
		{
			numbers.push_back(i); //create the number of values inside the vector to pick randomly - it will be between 1 and 2(n) - for 3 it will be between 1 and 6
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				board[i][j] = 0; //initialize board to 0's
			}
		}
	}


	//working
	void genInitialState() //randomly generates the numbers
	{
		int temp;				//temporary value to hold the numbers in the vector [so as to switch the value with the last] 
		int size;				//Size of the vector - to pick a random number between the size of the vector and 0
		int randomNumberZ;		//random number generated for vector position
		int randomNumberX;		//random number generated for row position
		int randomNumberY;		//randomNumber Generated for col position

		while (!numbers.empty()) //while vector numbers is not empty fill the positions
		{
			size = numbers.size();				//get vector size
			randomNumberX = rand() % rows;		//get random position for row
			randomNumberY = rand() % rows;		// get random position for col
			randomNumberZ = rand() % (size);

			if (isTopZero(randomNumberX, randomNumberY) == true) //if it is top, make the exchange
			{
				board[randomNumberX][randomNumberY] = numbers[randomNumberZ];
				temp = numbers[randomNumberZ];
				numbers[randomNumberZ] = numbers[size - 1];
				numbers[size - 1] = temp;
				numbers.pop_back();
			}

		
		}
	}



	//working - double checked
	bool isGoalAchieved(int number, int row, int col) const
	{
		if (board[row][col] == number)
		{

			return true;
		}
		else
		{

			return false;
		}

	}

	//working
	int calculateDistance(int blockNumber, int rowTo, int colTo) const//calculates the distance between current position and desired position
	{
		int heuristicValueReturn = 0;
		int rowCurrent = 0;
		int colCurrent = 0;
		getBlockCurrentRowCol(blockNumber, rowCurrent, colCurrent); //get current position for block number

		if (board[rowTo][colTo] == 0)
		{
			heuristicValueReturn = heuristicValueReturn - 5;
		}

		if (colCurrent == colTo)
		{
			heuristicValueReturn = 10;
			return (100 - heuristicValueReturn * 10);
		}
		else if (colCurrent > colTo) //calculate distance
		{
			heuristicValueReturn = colCurrent - colTo;

			int row = rowCurrent;

			for (int col = colCurrent; col > 0; col--)
			{
				while (row >= 0)
				{
					if (board[row][col] != 0)
					{
						heuristicValueReturn++;
					}

					row--;

					if (row == rowTo && col == colTo)
					{
						break;
					}
				}
				if (row == rowTo && col == colTo)
				{
					break;
				}

				row = rows - 1;
			}

			return (100 - heuristicValueReturn * 10);

		}
		else if (colCurrent < colTo)
		{
			heuristicValueReturn = colTo - colCurrent;

			int row = rowCurrent;

			for (int col = colCurrent; col < rows; col++)
			{
				while (row >= 0)
				{
					if (board[row][col] != 0)
					{
						heuristicValueReturn++;
					}

					row--;

					if (row == rowTo && col == colTo)
					{
						break;
					}
				}

				if (row == rowTo && col == colTo)
				{
					break;
				}

				row = rows - 1;
			}

			return (100 - heuristicValueReturn * 10);
		}

		return 0;
	}

	//returns colNumber of the number in question [block number]
	int getBlockNumberCol(int blockNumber) const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j] == blockNumber)
				{
					return j;
				}
			}

		}
	}

	//working
	void getBlockCurrentRowCol(int blockNumber, int& rowFrom, int& colFrom) const//gets the current value for the block number
	{
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < rows; col++)
			{
				if (board[row][col] == blockNumber)
				{
					rowFrom = row;
					colFrom = col;
				}
			}
		}
	}

	//returns heurstic value
	int getHeuristicValue(Goal goal) const//check to see if goal is achieved
	{
		
		int rowBlock;
		int colBlock;
		getBlockCurrentRowCol(goal.number, rowBlock, colBlock);

		if (isGoalAchieved(goal.number, goal.row, goal.col) == true)
		{
			return 100;
		}
		else if (isBlockNumberTop(goal.number) && isTopZero(goal.row, goal.col) && (goal.row != getBlockNumberCol(goal.number)))  // if there is an opening
		{
			return 99;
		}
		else if (isBlockNumberTop(goal.number) && isTopZero(goal.row, goal.col))
		{
			return 95;
		}
		else if (isBlockNumberTop(goal.number) && isGoalSpaceEmpty(goal) && rowBlock == 0)
		{
			return 90;
		}
		else if (isBlockNumberTop(goal.number) && isGoalSpaceEmpty(goal) && rowBlock == 1)
		{
			return 85;
		}
		else if (isBlockNumberTop(goal.number) && isGoalSpaceEmpty(goal) && rowBlock == (rows - 1))
		{
			return 82;
		}
		else if (isBlockNumberTop(goal.number) && isColumnEmptyOfGoal(goal) && rowBlock == 0)
		{
			return 80;
		}
		else if (isBlockNumberTop(goal.number) && isColumnEmptyOfGoal(goal) && rowBlock == 1)
		{
			return 78;
		}
		else if (isBlockNumberTop(goal.number) && isColumnEmptyOfGoal(goal) && rowBlock == ( rows-1) )
		{
			return 77;
		}
		else if (isGoalSpaceEmpty(goal) && (howManyAboveBlockNumber(goal) == 1))
		{
			return 75;
		}
		else if (isGoalSpaceEmpty(goal) && (howManyAboveBlockNumber(goal) == 2))
		{
			return 70;
		}
		else if (isBlockNumberTop(goal.number) && rowBlock != (rows - 1))
		{
			return 68;
		}
		else if (isColumnEmptyOfGoal(goal) && (getRowPositionOfNumber(goal) > goal.row))
		{
			return 65;
		}
		else if (isColumnEmptyOfGoal(goal) && howManyAboveGoalPosition(goal) == 0)
		{
			return 60;
		}
		else if (isColumnEmptyOfGoal(goal) && howManyAboveGoalPosition(goal) == 1)
		{
			return 55;
		}
		else if (isColumnEmptyOfGoal(goal) && howManyAboveGoalPosition(goal) > 1)
		{
			return 50;
		}
		else if (isBlockNumberTop(goal.number))
		{
			return 45;
		}
		else
		{
			return 25;
		}
	}

	int getRowPositionOfNumber(Goal goal) const//return row number of the blocknumber in the goal
	{
		int row1 = 0;
		for (int col = 0; col < rows; col++)
		{
			for (int row = 0; row < rows; row++)
			{
				if (board[row][col] == goal.number)
				{
					row1 = row;
					return row;
				}
			}
		}
	}


	int howManyAboveGoalPosition(Goal goal) const
	{
		int numberCheck = 1;

		if (isTopZero(goal.row, goal.col))
		{
			return 0;
		}

		if (!(isTopZero(goal.row, goal.col)) && goal.row == 1 && isGoalSpaceEmpty(goal))
		{
			return 1;
		}

		if (board[goal.row][goal.col] != 0 && goal.row != 0)
		{

			for (int row = goal.row - 1; row >= 0; row--)
			{
				if (board[row][goal.col] != 0)
				{
					numberCheck++;
				}
			}
		}
		
		return numberCheck;
	}

	int howManyAboveBlockNumber(Goal goal) const
	{
		int row;
		int col;
		int howManyAbove = 0;
		getBlockCurrentRowCol(goal.number, row, col);

		if (row == 0)
		{
			return howManyAbove;
		}

		for (row = row - 1; row >= 0; row--)
		{

			if (board[row][col] != 0)
			{
				howManyAbove++;
			}
		}

		return howManyAbove;
	}

	bool isBlockNumberTop(int blockNumber) const //checks to see if blockNumber is top
	{

		int rowBlock = 0;
		int colBlock = 0;
		int test = 0;
		for (int col = 0; col < rows; col++)
		{
			for (int row = 0; row < rows; row++)  //gets current position of blockNumber
			{
				if (board[row][col] == blockNumber)
				{
					rowBlock = row;
					colBlock = col;
					test = 1;
					break;
				}
			}

			if (test == 1)
			{
				break;
			}
		}

		if (isTopNotZero(rowBlock, colBlock))
		{
			return true;
		}
		else
		{
			return false;
		}


	}

	bool isColumnEmptyOfGoal(Goal goal) const //checks if column of goal position is empty
	{
		if (board[0][goal.col] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isGoalSpaceEmpty(Goal goal) const //checks to see if there is an opening in the desired position of the row and col of the goal
	{
		if (board[goal.row][goal.col] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}


	//working this tests if there is a position available which is top
	bool isTopZero(int randomNumberRows, int randomNumberCols) const
	{
		if (board[randomNumberRows][randomNumberCols] == 0)
		{
			if (randomNumberRows == (rows - 1))
			{
				return true;
			}
			else if (randomNumberRows < (rows - 1) && board[randomNumberRows + 1][randomNumberCols] != 0)
			{
				return true;
			}
		}

		return false;
	}


	//test to see if there is a blocknumber is top
	bool isTopNotZero(int row, int col) const
	{
		if (!(board[row][col] == 0))
		{
			if (row == 0)
			{
				return true;
			}
			else if (row != 0 && board[row - 1][col] == 0)
			{
				return true;
			}

		}

		return false;
	}

	//display board
	void displayBoard() const
	{
		cout << "  ";
		cout << endl;

		for (int i = 0; i < rows; i++)
		{
			cout << "  |";
			cout << " ";

			for (int j = 0; j < rows; j++)
			{
				cout << board[i][j];
				cout << " | ";
			}
			cout << endl;
			cout << "   ";

			cout << endl;
		}
	}

	//makes moves
	void getMoveThenMakeMove(int blockNumber, int rowTo, int colTo)
	{
		//makes move
		int rowCurrent = 0;
		int colCurrent = 0;
		getBlockCurrentRowCol(blockNumber, rowCurrent, colCurrent);
		board[rowCurrent][colCurrent] = 0;
		board[rowTo][colTo] = blockNumber;
	}

	bool dangerPositionAvailable(int blockNumber, int blockRow, int blockCol, Goal goal) 
	{
		if (board[blockRow][blockCol] == blockNumber && isTopNotZero(blockRow, blockCol)) //check to see if the block number is top, and the block is at that paticular position
		{
			if (isTopZero(goal.row, goal.col) && (goal.col != blockCol))
			{
				getMoveThenMakeMove(blockNumber, goal.row, goal.col);
				cout << "danger position available completed" << endl;
				return true;
			}
		}
	}

	//finds all current available positions - is working [double checked]
	void availablePositions(vector< positionsAvailable >& posAvail) const
	{

		for (int col = 0; col < rows; col++)
		{
			for (int row = rows - 1; row >= 0; row--)
			{
				if (board[row][col] == 0 && isTopZero(row, col))
				{
					positionsAvailable posAv;
					posAv.rowAv = row;
					posAv.colAv = col;
					posAvail.push_back(posAv);
					break;
				}
			}
		}
	}


	bool numberUsedIn(int number, vector< int > numberUsed) const
	{
		if (numberUsed.size() == 0)
		{
			return false;
		}

		if (numberUsed.size() > 0)
		{
			for (unsigned int i = 0; i < numberUsed.size(); i++)
			{
				if (number == numberUsed[i])
				{
					return true;
				}
			}
		}

		return false;
	}

	//finds all top values for conjunctive goals [if it is already a goal that has been completed]
	void topValues(vector< positionsTop >& tops, vector<int> numberUsed) const
	{
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < rows; col++)
			{
				if (isTopNotZero(row, col))
				{
					positionsTop top;
					top.rowTop = row;
					top.colTop = col;
					top.blockNumber = board[row][col];
					if (!numberUsedIn(top.blockNumber, numberUsed))
					{
						tops.push_back(top);
					}
				}
			}
		}
	}


	void topValuesDisjunctive(vector< positionsTop >& tops) const
	{
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < rows; col++)
			{
				if (isTopNotZero(row, col))
				{
					positionsTop top;
					top.rowTop = row;
					top.colTop = col;
					top.blockNumber = board[row][col];
					tops.push_back(top);
				}
			}
		}
	}


	//working - double checked 
	void operator =( State s)
	{
		rows = s.rows;
		totalCount = s.totalCount;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				board[i][j] = s.board[i][j]; //initialize board to 0's
			}
		}
	}

	bool operator==(const State s) const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j] != s.board[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

};

void State::destroyBoard()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] board[i];
	}

	delete[] board;
}

State::~State()
{
	/*
	for (int i = 0; i < rows; i++)
	{
		delete[] board[i];
	}

	delete[] board;
	*/
	
}

#endif /* State_h */
