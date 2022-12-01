
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <ctime>
#include <iterator>
#include <vector>
using namespace std;

template <class Type>
class Aggregate{
	private:
		vector<Type> list;
	public:
		Aggregate(Type *input, int length)
		{
			for(int i = 0 ; i < length; i++)
			{
				list.push_back(input[i]);	
			}	
		}	
		
		bool seqSearch(Type item, int &loc);
		void bubbleSort();
		void binarySearch(Type item, int &loc);
		void print();
};

template<class Type>
bool Aggregate<Type>::seqSearch(Type item, int& loc)
{
	for(int i = 0; i < list.size(); i++)
	{
		if(list[i] == item)
		{
			loc = i;
			return true;
		}
	}
	
	return false;
}

template<class Type>
void Aggregate<Type>::bubbleSort()
{
	int temp;
	int test = 0;
	do {
			 test = 0;
					
			for( int i =0; i < list.size(); i++)
			{
				if(list[i] > list[i+1] && (i+1) != list.size())
						{
							temp = list[i+1];
							list[i+1] = list[i];
							list[i] = temp;
							test++;
						}
			}
		} while (test > 0);
}

template<class Type>
void Aggregate<Type>::binarySearch(Type item, int &loc)
{
	int end = list.size();
	int start = 0; 
	int mid; 
	
	  while(end >= start)
       { 
		   mid = (end + start)/2;
		 if(list[mid] < item)
		   {
			   start = mid + 1; 
		   }
		   else if(list[mid] > item)
		      {
				  end = mid - 1; 
			  } else
                  {
					  loc = mid;
					  break;
				  }
	   }
	   
}

template<class Type>
void Aggregate<Type>::print()
{
	cout << "Array printing : ";
	for( int i = 0; i < list.size(); i++)
	{
		cout << list[i] << " ";
	}
	cout<<endl;
}


int main()
{
	srand(time(0));
	int array[10];
	int length = 10;
	int randomNumber;
	int location = 0;
	int searchValue = 4;
	int searchValue1 = 4;
	
	for(int i = 0; i < 10; i++)
	{ 
	  randomNumber = rand() % 10;
	  array[i] = randomNumber;
			
	   for(int j = 0; j < i; j++)
	      {
			if(array[j] == array[i])
			  { 
				
				i--;
	            break; 			
			  }		  
		  }
	}
	
	Aggregate<int> Agg(array, 10);
	
	Agg.print();
	Agg.seqSearch(searchValue, location);
	cout << "Value has been found at position " << location << endl;
	Agg.bubbleSort();
	Agg.binarySearch(searchValue1, location);
	Agg.print();
	cout << "Value has been found at position " << location << endl;
	
	
}



