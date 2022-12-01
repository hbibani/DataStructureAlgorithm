#include <iostream>
#include<iterator>
#include<list>


using namespace std;

int main()
{
  list<int> numbers;
  list<int>::iterator it;
  
	numbers.push_front(9);
	numbers.push_front(13);
	numbers.push_front(14);
	
	it = numbers.begin();
	
//	for(it; it!=numbers.end(); ++it)
//	{
//		//cout << *it;
//	}

//	advance(it, 2);
	cout << *it;
}
