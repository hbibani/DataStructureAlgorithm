#include <iostream>
#include <cstdlib>
#include<ctime>
#include<vector>
#include<list>
#include<iterator>

using namespace std;

#include "unorderedlinkedList.h"

class State
{
	public:
	  State( );
	  void generateSequenceArray( );
	  void generateSequenceVector( );
	  void generateSequenceVectorFast( );
	  void generateSequenceList( );
	  void printSequenceList( );
	  void printArray( );
	  void printVector( );
	  vector< int > vectorCount;
	  list< int >::iterator it;
	  void printSequenceListOutside( );
	  void generateSequenceListOutside( );
	  void checkIfInSamePosition( );
	  void printSequenceListSame( );
	  bool operator==( State s );
	  bool operator!=( State s );
	  bool inSamePosition;
	  int numberInSamePosition;
	private:
	  int array[ 9 ];
	  int size;
	  int used;
	  list< int > list;
	  vector< int > vector;
	  unorderedLinkedList< int > listUnordered;
	  linkedListIterator< int > itOut;
	  int arraySame[ 9 ];
	 
};

bool State::operator!=( State s )
{
	for( int i = 0 ; i < 9 ; i++ )
	{
		if( vector[ i ] != s.vector[i] )
		{
			return true;
		}
	}
	
	return false;
}

bool State::operator==( State s )
{
	for( int i = 0 ; i < 9 ; i++ )
	{
		if( vector[ i ] != s.vector[ i ] )
		{
			return false;
		}
	}
	
	return true;
}

void State::printSequenceListOutside( )
{
	for( itOut = listUnordered.begin( ) ; itOut !=listUnordered.end( ) ; ++itOut )
	  {
	    cout << ( *itOut ) << " ";
	  }
  
  cout << " Iterations: " << used << " | | " << "Total Number in Same Position" << numberInSamePosition;

  cout << endl;
}

void State::checkIfInSamePosition( )
{
	numberInSamePosition = 0;
	
	int i = 0; 
	for( itOut = listUnordered.begin( ) ; itOut != listUnordered.end( ) ; ++itOut ) 
	{
		if( ( *itOut ) == arraySame[ i ] )
		{
			numberInSamePosition++;
		}
		i++;
	}
	
	if(numberInSamePosition == 9)
	{
		inSamePosition = true;
	}
	else
	{
		inSamePosition = false;
	}
}

void State::generateSequenceListOutside( )
{ 
	nodeType< int >* current;
	current = listUnordered.getKThElement( 0 );
	 
   for( int i = 1 ; i < 7 ; i ++ )
	{
 		used++;
  		int randomNumberX = rand( ) % 9;
      	current = listUnordered.getKThElement( randomNumberX );
      	
      	if( current->info == 0 )
      	{
      		current->info = i;
		}
     	 else
      	{
         i--;
      	}
	}
}

void State::printSequenceList( )
{
  for( it = list.begin( ) ; it !=list.end( ) ; ++it )
  {
    cout << ( *it ) << " ";
  }
  cout << " Iterations: " << used;
  cout << endl;
}

void State::generateSequenceList( )
{
  for( int i = 1 ; i < 7 ; i ++ )
  {
      int randomNumberX = rand( ) % 9;
      used++;
      it = list.begin( );
      for( int j = 0; j <= randomNumberX; j++ )
      {
      	it++;
	  }
	  
      if( *it == 0 )
      {
        ( *it ) = i;
      }
      else
      {
        i--;
      }
  }
}

void State::printArray( )
{
  for( int i = 0 ; i < 9 ; i++ )
  {
    cout << array[ i ] << " ";
  }

  cout << " Iterations: " << used;
  cout << endl;
}

void State::printVector( )
{
  for( int i = 0 ; i < 9 ; i++ )
  {
    cout << vector[ i ] << " ";
  }

  cout << "Iterations :" << used;
}

void State::generateSequenceArray( )
{
  for(int i = 1 ; i < 7 ; i++ )
  {
    int randomNumberX = rand( ) % 9;
    used++;
    
    if( array[ randomNumberX ] == 0 )
    {
    	array[ randomNumberX ];
    }
    else
    {
    	i--;
    }
    
  }
}

void State::generateSequenceVectorFast( )
{
  for( int i = 0 ; i < 7 ; i++ ) //use while loop
   {
      int randomNumberX  = rand( )% 9;
      used++;
      
      if( vector[ randomNumberX ]  == 0 )
      {
        vector[ randomNumberX ] = i;
      }
	  else
	  {
	     i--;
	  }
   }
}

State::State()
{
  for(int i = 0 ; i < 9 ; i++ )
  {
    array[ i ] = 0;
    vector.push_back( 0 );
    vectorCount.push_back( i );
    list.push_front( 0 );
    listUnordered.insertLast( 0 );
  }
  
  inSamePosition = false;
  size = 9;
  used = 0;
  
  	arraySame[ 0 ] =  2;
	arraySame[ 1 ] =  1;
	arraySame[ 2 ] =  5;
	arraySame[ 3 ] =  4;
	arraySame[ 4 ] =  0;
	arraySame[ 5 ] =  0;
	arraySame[ 6 ] =  6;
	arraySame[ 7 ] =  0;
	arraySame[ 8 ] =  3;
}

int main()
{
	State array[ 10 ];
	unorderedLinkedList< State > ulState;
	linkedListIterator< State > itLinkedList;
	int totalNumberSame = 0;
   
	for( int i = 0 ; i < 1000 ; i++ )
	{
		State s;
		s.generateSequenceListOutside( );
		s.checkIfInSamePosition( );
		ulState.insertFirst( s );
	}

	for( itLinkedList = ulState.begin( ) ; itLinkedList != ulState.end( ) ; ++itLinkedList )
	{
		if( ( *itLinkedList ).inSamePosition )
		{	
			 totalNumberSame++;
		}
		
		cout << "Number in same position: " << (*itLinkedList).numberInSamePosition << endl;
	}
	
	cout << "Total Number Which are the same is : " << totalNumberSame;

	return 0;
}
