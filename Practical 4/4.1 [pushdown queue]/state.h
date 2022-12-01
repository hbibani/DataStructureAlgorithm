

const int BOARDSIZE = 3;
const int NUMBER_OF_BLOCKS = 6;

class State {
private:
	int grid[BOARDSIZE][BOARDSIZE];
	stack<int> numberHolder;
	queue<int> numberHolderQueue;
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
	void pushDownQueue();
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

void State::pushDown()
{

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = BOARDSIZE - 1; j >= 0; j--)
		{
			if (grid[j][i] > 0)
			{
				numberHolder.push(grid[j][i]);

			}

			grid[j][i] = 0;

		}

		int	size = numberHolder.size();

		for (int k = 0; k < size; k++)
		{
			grid[k][i] = numberHolder.top();
			numberHolder.pop();
		}
	}

}


void State::pushDownQueue()
{
	for (int col = 0; col < BOARDSIZE; col++)
	{
		for (int row = 0; row < BOARDSIZE; row++)
		{
			if (grid[row][col] != 0)
			{
				numberHolderQueue.push(grid[row][col]);
				grid[row][col] = 0;
			}
		}

		int rows = 0;

		while (!numberHolderQueue.empty())
		{
			grid[rows][col] = numberHolderQueue.front();
			numberHolderQueue.pop();
			rows++;
		}

	}

}

