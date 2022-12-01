#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

#include "state.h"

bool search( stack< State > states , State target )
{
	if ( states.empty( ) )
	{
		return false;
	}

	if ( states.top( ) == target )
	{
		states.top( ).printBoard( );
		return true;
	}
	
	states.pop( );
	return search( states , target );
	
}

int main( )
{
	srand( time( 0 ) );
	State target;
	target.printBoard( );
	stack<State> states;
	
	for ( int i = 0 ; i < 10 ; i++ )
	{
		State s;
		
		if ( i == 9 )
		{
			states.push( target );
		}
		else
		{
			states.push( s );
		}
	}

	if ( search( states, target ) )
	{
		cout << "Found it! " << endl;
		for(int i = 0 ; i < states.size( ) ; i++)
		{
			states.pop();
		}
	}
	else
	{
		cout << "Did not found it!" << endl;	
	}
		
	return 0;
}

