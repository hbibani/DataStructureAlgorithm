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
	
	private:
		int array[9];
		int size;
		int used;
		vector<int> vector;
		int arraySame[9];
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

random::random()
{
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
	arraySame[9] =  0;
	size = 10;
	used = 0;
}


int main()
{
	srand(time(0)); 
	random r;	
	r.generateSequenceVector();
	random array[10];
	
	for(int i= 0; i < 10; i++)
	{
		array[i].generateSequenceVectorFast();
		array[i].printVector();
		cout<<endl;
	}
	
}
