#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <utility>
#include <string>
#include <fstream>

using namespace std;

bool searchMap( map < string , int > &maps , string name )
{
	map < string , int >::iterator mapIt;
	for( mapIt = maps.begin( ) ; mapIt !=maps.end() ; mapIt++ )
	{
		if( mapIt->first == name ) 
		{
			mapIt->second += 1;   //search file for name, and if present, add a number to it
			return true;
		}
	}
	
	return false;
}

int main( )
{
	ifstream fin;
	
	if( fin.fail( ) )
	{
		cout << "Inpout file opening failed \n";
		exit( 1 );
	}	
	
	fin.open( "names.txt" );
	
	map < string , int >  maps;
	map < string , int >::iterator mapIt;
	string name;
	string clearString;
	char letter;
	char clearChar;

	fin.get( letter );
	
	
	while( !fin.eof( ) )
	{
		if( letter != '\n' && letter != ' ' )
		{
			name = name + letter;	
			fin.get( letter );                //have to use fin.get and not "<<" because it is ignores white spaces [and because of this the if statement "'/n' and ' '" won't be tested	
		}
		else
		{
			if(!searchMap( maps , name ))             
				maps.insert( make_pair( name, 1 ) );
				
			name = clearString;               // you can't clear a string 
			letter = clearChar;				 // you can't clear a char; so we make another char which hasn't been initiated
			fin.get( letter );
		}
		
		if( fin.eof( ) )
		{
			if(!searchMap(maps, name))
				maps.insert(make_pair(name,1)); //off by 1, the last name doesn't get inserted [because of EOF has been hit.
		}
	}
	
	
	cout << endl;
	
	for( mapIt = maps.begin( ) ; mapIt != maps.end( ) ; mapIt++ )
	{
		cout << mapIt->first << "\t\t" << mapIt->second << endl;
	}
	

}
