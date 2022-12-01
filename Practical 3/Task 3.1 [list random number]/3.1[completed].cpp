#include <iostream>
#include <cstdlib>
#include<ctime>
#include <vector>
#include<iterator>
#include<list>

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
		vector<int> vectorCount;
		vector<int> vector;
	private:
		int array[9];
		int size;
		int used;	
};

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

void random::generateSequenceVector( )
{
	for( int i = 0 ; i < 7 ; i++ ) //use while loop
	{ 
		int randomNumberX  = rand( )% 9;
		used++;
		
		if( vector[ randomNumberX ] == 0 )
		{
			vector[ randomNumberX ] = i; 
		}
		else 
		{
		 i--;
		}
	}
}

random::random( )
{
	for( int i = 0 ; i < 9 ; i++ )
	{
		array[ i ] = 0;
		vector.push_back( 0 );
		vectorCount.push_back( i );
	}
	
	size = 10;
	used = 0;
}


int main( )
{
	srand( time( 0 ) ); 
	random r;	
	r.generateSequenceVector( );
	list< random > list;
	//list< random >::iterator its;
	
	
	for( int i= 0 ; i < 10 ; i++ )
	{
		random r;
		r.generateSequenceVector( );
		list.push_back( r );
	}
	
//		
//	for(its = list.begin(); its !=list.end() ;its++)
//	{
//		its->printVector( );
//	}
	
	while( !list.empty( ) )
	{
		list.front( ).printVector( );
		list.pop_front( );
		cout<<endl;			
	}
}

