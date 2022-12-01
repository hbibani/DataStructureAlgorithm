#include <iostream>

using namespace std;

float powerTo( int x , int y )
{
	if( y >= 0 )
	{
		if( y == 0 )
		{
			return 1;
		}
		else if( y == 1 )
		{
			return x;
		}
		else if( y > 1 );
		{
			return x * powerTo( x , y-1 );
		}
	}
	else if( y < 0 ) 
	{
		return 1/powerTo( x , -y );
	}
}

int main( )
{
	float x = powerTo( 4 , -2 );
	float y = powerTo( 4 , 2 );
	cout << "X = " << x << endl;
	cout << "Y = " << y << endl;
}
