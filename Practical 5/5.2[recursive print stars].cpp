#include <iostream>

using namespace std;

int recursiveLine( int stars )
{
	if( stars == 0 )
	{
	 return 0;	
	}
	else if( stars == 1 )
	{
		cout << "*" << endl;
	}	
	else
	{
	 recursiveLine( stars - 1 );
	}
	
	for( int i = 0 ; i <= stars ; i++ )
	{
			cout << "*";
	}
	cout << endl;
}

int recursive( int stars , int starsMax )
{
	for( int i = 0 ; i <= stars ; i++ )
	{
			cout << "*";
	}
	
	cout << endl;
	
	if(stars == 0)
	{
		recursiveLine( starsMax );
		return 0;
	}
	else 
	{
		recursive( stars - 1 , starsMax );
	}
}

void printStarLine( int n ) 
{
	if( n < 1 )
	{
	  cout << endl;
	  return;
	}
	  
	cout << "*";
	printStarLine( n-1 );
}
 
void printStars( int m )
{
    if ( m == 0 )
	{
        return;
    }
    
	printStarLine( m );
	printStars( m-1 );	
	printStarLine( m );
}

int main( )
{
	int amount;
	cout << "Enter the stars" << endl;
	cin >> amount;
	printStars( amount );
	
	return 0;
}
