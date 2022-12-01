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
		vector<int> vectorCount;
	
	private:
		int array[9];
		int size;
		int used;
		vector<int> vector;
		
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
	
	cout << "Iterations :" << used;	

}


void random::generateSequenceArray()
{
	 for(int i = 1; i < 7; i++) //use while loop
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
	
	size = 9;
	used = 0;
}

int main()
{
	srand(time(0)); 
	random r;	
	r.generateSequenceVector();
	random array[10];
	vector<random> randomNumbers; 
	
	for(int i= 0; i < 10; i++)
	{
		random r;
		r.generateSequenceVector();
		randomNumbers.push_back(r);
		array[i].printVector();
		cout<<endl;
	}	
}
