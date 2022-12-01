#include <iostream>
#include <cstdlib>
#include<ctime>
#include <vector>


using namespace std;

class random
{
	public:
		random();
		void generateSequenceArray();
		void generateSequenceVector();
		void generateSequenceVectorFast();
		void printArray();
		void printVector();
		bool checkIfSame();
		vector<int> vectorCount;
		void generateRandomMatrix();
		void printMatrix();
	
	private:
		int array[9];
		int size;
		int used;
		vector<int> vector;
		int arraySame[9];
		int **board;
};


bool random::checkIfSame()
{
  for(int i = 0 ; i < vector.size(); i++)
  {
  	 if(vector[i] != arraySame[9])
  	 {
  	 	return false;
	}
  }	
  
  return true;
}

void random::printArray()
{
	for(int i = 0; i < 9; i ++) 
	{
		cout << array[i] << " ";
	}
	cout <<" Iterations : " << used;
	cout << endl;
}

void random::printVector()
{
	for(int i =0 ; i < 9; i++)
	{
		cout << vector[i]	<< " ";
	}
	
	cout << "Iterations: " << used;	
	
	if(checkIfSame())
	{
		cout << " Same: Yes";
	}
	else
	{
		cout << " Same: No";
	}

}


void random::generateSequenceArray()
{
	 for(int i = 0; i < 7; i++) //use while loop
	 { 
	  	int randomNumberX  = rand()% 9;
	  	used++;
	  	if(array[randomNumberX] == 0)
	    {
	    	array[randomNumberX] = i; 
	    }
		else 
		{
		 i--;
		}
	 }

}

void random::generateSequenceVectorFast()
{
	int sizeS = 0;
	int randomNumberX;
	int temp;
	int test;

	for(int i = 1 ; i < 7; i++)
	{
		sizeS = vectorCount.size();
		randomNumberX  = rand()% (sizeS);
		test = vectorCount[randomNumberX];
		used++;
		vector[test] = i;
		temp = vectorCount[randomNumberX];
		vectorCount[randomNumberX] = vectorCount[sizeS-1];
		vectorCount[sizeS-1] = temp;
		vectorCount.pop_back();		 	
	}
}

void random::generateSequenceVector()
{
	for(int i = 0; i < 7; i++) //use while loop
	 { 
	  	int randomNumberX  = rand()% 9;
	  	used++;
	  	if(vector[randomNumberX] == 0)
	    {
	    	vector[randomNumberX] = i; 
	    }
		else 
		{
		 i--;
		}
	 }
}


void random::printMatrix()
{
	
	int rows = 3;
	for ( int i = 0 ; i < rows ; i++ )
		{
			cout << " _____";
		}

		cout << endl;

		for ( int row = 0 ; row < rows ; row++ )
		{
			cout << "|     ";
			for ( int i = 0 ; i < rows ; i++ )
			{
				if  ( i != 0 )
				{
					cout << "|     ";
				}
			}
			cout << "|" << endl;

			for ( int i = 0; i < ( rows ); i++ )
			{
				cout << "|  " << board[ row ][ i ] << "  ";
			}
			cout << "|";
			cout << endl;
			cout << "|";

			for ( int col1 = 0 ; col1 < rows ; col1++ )
			{
				cout << "_____|";
			}
			cout << endl;

		}
		cout << endl;
}

void random::generateRandomMatrix()
{
	int randRows;
	int randCols;
	for(int i = 0 ; i < 7; i++)
	{
		randRows = rand() % 3;
		randCols = rand() % 3;
		
		if(board[randRows][randCols] == 0)
		{
			board[randRows][randCols] = i;
		}
		else
		{
			i--;
		}
		
	}	
}


random::random()
{
	 
	 board = new int* [ 3 ];
	 
	 
	 for(int i =  0 ; i < 3; i++)
	 {
	    board[i] = new int[3];
	 }
	 
	 for(int i = 0; i < 3; i ++)
	 {
	 	for(int j = 0 ; j < 3; j++)
	 	{
	 		board[i][j]  = 0;
		}
	 }
	
	for(int i = 0 ; i < 9; i++)
	{
		array[i]=0;
		vector.push_back(0);
		vectorCount.push_back(i);
	}
	
	arraySame[0] =  2;
	arraySame[1] =  1;
	arraySame[2] =  5;
	arraySame[3] =  4;
	arraySame[4] =  0;
	arraySame[5] =  0;
	arraySame[6] =  6;
	arraySame[7] =  0;
	arraySame[8] =  3;
	size = 10;
	used = 0;
}


int main()
{
	srand(time(0)); 
	random r;	
	r.generateSequenceVector();
	random array[10];
	r.generateRandomMatrix();
	r.printMatrix();
	
//	
//	for(int i= 0; i < 10; i++)
//	{
//		array[i].generateSequenceVectorFast();
//		array[i].printVector();
//		cout<<endl;
//	}
	
}
