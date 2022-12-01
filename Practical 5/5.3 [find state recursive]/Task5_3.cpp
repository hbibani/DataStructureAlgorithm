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
	if ( states.size( ) == 0 )
	{
		return false;
	}
	else if ( states.top() == target )
	{
		states.top( ).printBoard( );
		return true;
	}
	else
	{
		if ( states.size( ) > 0 )
		{
			states.pop( );
		}
		
		return search( states , target );
	}
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
		states.push( s );
	}

	if ( search( states, target ) )
		cout << "Found it! " << endl;
	else
		cout << "Did not found it!" << endl;

	return 0;
}

