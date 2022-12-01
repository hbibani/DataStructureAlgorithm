#include <iostream>
#include <cstdlib>
#include<ctime>
#include<vector>
#include<list>
#include<iterator>

using namespace std;


#include "orderedLinkedList.h"
#include "unorderedlinkedList.h"

class State
{
public:
  State();
  void generateSequenceArray();
  void generateSequenceVector();
  void generateSequenceVectorFast();
  void generateSequenceList();
  void printSequenceList();
  void printArray();
  void printVector();
  vector<int> vectorCount;
  list<int>::iterator it;
  bool operator==(State s);
  bool operator!=(State s);
  void printSequenceListOutside( );
  void generateSequenceListOutside( );
  void generateSequenceListOrdered( );
  void printSequenceListOutsideOrdered( );
  bool operator<(const State r) const;
private:
  int array[9];
  int size;
  int used;
  list<int> list;
  vector<int> vector;
  orderedLinkedList<int> listOrdered;
  unorderedLinkedList<int> listUnordered;
  linkedListIterator<int> itOut;


};

bool State::operator!=(State s)
{
	for(int i = 0 ; i < 9; i++)
	{
		if(vector[i] != s.vector[i])
		{
			return true;
		}
	}
	
	return false;
}

bool State::operator==(State s)
{
	for(int i = 0 ; i < 9; i++)
	{
		if(vector[i] != s.vector[i])
		{
			return false;
		}
	}
	
	return true;
}

void State::printSequenceListOutside( )
{

for( itOut = listUnordered.begin( ); itOut !=listUnordered.end( ); ++itOut )
  {
    cout << (*itOut) << " ";
  }
  cout << " Iterations: " << used;
  cout << endl;
}

void State::printSequenceListOutsideOrdered( )
{

for( itOut = listOrdered.begin( ); itOut !=listOrdered.end( ); ++itOut )
  {
    cout << (*itOut) << " ";
  }
  cout << " Iterations: " << used;
  cout << endl;
}

void State::generateSequenceListOutside( )
{ 
	 nodeType<int>* current;
	 current = listUnordered.getKThElement(0);
	 
	  for( int i = 1 ; i < 7 ; i ++ )
	  {
	 		used++;
	  		int randomNumberX = rand( ) % 9;
	      	current = listUnordered.getKThElement(randomNumberX);
	      	
	      	if(current->info == 0)
	      	{
	      		current->info = i;
			}
	     	 else
	      	{
	         i--;
	      	}
	  }
}

void State::generateSequenceListOrdered()
{
	int sizeS = 0;
	int randomNumberX;
	int temp;
	int test;
	
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
	
	for(int i = 0 ; i < 9; i++)
	{
		listOrdered.insert(array[i]);
	}
}

void State::printSequenceList()
{

  for( it = list.begin( ); it !=list.end( ); ++it )
  {
    cout << (*it) << " ";
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
    cout << array[i] << " ";
  }

  cout << " Iterations: " << used;
  cout << endl;
}

void State::printVector()
{
  for(int i = 0 ; i < 9 ; i++)
  {
    cout << vector[i] << " ";
  }

  cout << "Iterations :" << used;
}

void State::generateSequenceArray()
{
  for(int i = 1; i < 7; i++)
  {
    int randomNumberX = rand() % 9;
    used++;
    if(array[randomNumberX] == 0)
    {
      array[randomNumberX];
    }
    else
    {
      i--;
    }
  }
}

void State::generateSequenceVectorFast()
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



State::State()
{
  for(int i = 0 ; i < 9 ; i++ )
  {
    array[i] = 0;
    vector.push_back(0);
    list.push_front(0);
    listUnordered.insertLast(0);
  }
  
  for(int i = 1 ; i < 7 ; i++)
  {
  	vectorCount.push_back(i);
  }
  
  size = 9;
  used = 0;
}

int main( )
{
  unorderedLinkedList< State > ulState;
  linkedListIterator< State > itLinkedList;
  
  for( int i = 0 ; i < 10 ; i++ )
  {
  	State s;
  	s.generateSequenceListOrdered( );
  	ulState.insertFirst( s );  	
  }
  
  	for( itLinkedList = ulState.begin( ) ; itLinkedList != ulState.end( ) ; ++itLinkedList )
	{
		( *itLinkedList ).printSequenceListOutsideOrdered( );
	}
  

return 0;

}
