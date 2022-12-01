
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
}



void State::pushDown( )
{

	int test = 0;
	for ( int i = 0 ; i < BOARDSIZE ; i++ )
	{
		linkedStackType<int> numberHolder;
			
		for ( int j = BOARDSIZE - 1 ; j >= 0 ; j-- )
		{
			if ( grid[ j ][ i ] > 0 )
			{
				numberHolder.push( grid[ j ][ i ]);
				test++;
			}
		}

		if ( test < 3 )
		{
			for ( int j = 0 ; j < BOARDSIZE ; j++ )
			{
				grid[ j ][ i ] = 0;
			}

			for ( int k = 0 ; k < test ; k++ )
			{
				grid[ k ][ i ] = numberHolder.top( );
				numberHolder.pop( );
			}
			
			test = 0;
		}
		else
		{
			for ( int i = 0 ; i < test ; i++ )
			{
				numberHolder.pop( );
			}
			
			test = 0;
		}
	}

}

