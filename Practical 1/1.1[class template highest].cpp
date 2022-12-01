#include <iostream>
using namespace std;

template<class Type>
void funcExp(Type list[], int size)
{
	Type x = list[0];
	Type y = list[size -1];
	
	for(int i = 0 ; i < size; i++)
	{
		if (x < list[i])
		{
			 x = list[i];   //gets the heighest number [or alphabetical order]
		}
		
		if(y>list[size-1-i])
		{
		     y = list[size-1-i];  //gets the lowest number [or alphabetical order]
		}
	}
	
	for(int i = 0 ; i < 10; i++)
	{
		cout << list[i] << endl;
	}
}

int main()
{
		int list[10] = {5,3,2,10,4,19, 45, 13, 61, 11};
		string strList[] = {"One", "Hello", "Four", "Three", "How", "Six"};
		
		funcExp(list,10);
		funcExp(strList, 6);

		return 0;
}

