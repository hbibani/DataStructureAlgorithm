#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <ctime>
#include <iterator>
#include <vector>




using namespace std;

template<class Type>
class Aggregate
{
	private:
		vector<Type> list;
	public:
		Aggregate(Type * input, int length)
		{
			for(int i = 0 ; i < length ; i++)
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
bool Aggregate<Type>::seqSearch(Type item, int &loc)
{
	
	for(int i = 0 ; i < list.size() ; i++)
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
void Aggregate<Type>::binarySearch(Type item, int& loc)
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
		   } 
		   else
           {
			  loc = mid;
			  break;
		   }
	   }
}


template<class Type>
void Aggregate<Type>::print()
{
	for(int i = 0 ; i < list.size(); i++)
	{
		cout << list[i] << " "; 
		
	}
	cout << endl;
}


int main()
{
   int arrayInt[10] = { 8 , 3 , 5 , 7 , 1 , 9 , 2 ,4 , 6 , 10 };
   char arrayChar[10] = { 'k' , 's' , 'q' , 'w' , 'g' , 'e' , 'a' , 'r' , 'o' , 'm' };
   
   Aggregate<int> integerAgg(arrayInt, 10);
   Aggregate<char> characterAgg(arrayChar, 10);
   
   integerAgg.bubbleSort();
   characterAgg.bubbleSort();
   
   integerAgg.print();
   cout << endl;
   characterAgg.print();
	
	
	
}
