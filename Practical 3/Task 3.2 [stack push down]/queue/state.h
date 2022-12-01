
const int BOARDSIZE = 3;
const int NUMBER_OF_BLOCKS = 6;

class State {
private:
	int grid[BOARDSIZE][BOARDSIZE];

public:
	State() {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				grid[i][j] = rand() % 7;
	}

	//For Task 3.4
	bool operator==(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.grid[i][j] != grid[i][j])
					return false;
		return true;
	}

	//For Task 3.4
	bool operator!=(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.grid[i][j] != grid[i][j])
					return true;
		return false;
	}

	void printBoard();
	void pushDown();
};

void State::printBoard() {
	cout << endl;

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			cout << " " << grid[BOARDSIZE - i - 1][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	cout << endl << " Test : " << endl;
	cout << grid[2][0] << " " << grid[1][0] << " " << grid[0][0];
	cout << endl;
}

void State::pushDown()
{

		
	for (int i = 0; i < BOARDSIZE; i++)
	{
		queue<int> numberHolder;
		//pushing it into stack
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (grid[j][i] > 0)
			{
				numberHolder.push(grid[j][i]);
			}
		}

		int size = numberHolder.size();
	
		
		if (numberHolder.size() < 3) //checking to see if it is less than 3
		{
			
			for (int j = 0; j < BOARDSIZE; j++)
			{
				grid[j][i] = 0; //zero values
			}

			for (int k = 0; k < size; k++)
			{
				grid[k][i] = numberHolder.front(); //re-assign values from bottom
				numberHolder.pop(); //pop the stack
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				numberHolder.pop(); //else pop off the values which are greater than 3 [no need to change]
			}
		}
	}
}

