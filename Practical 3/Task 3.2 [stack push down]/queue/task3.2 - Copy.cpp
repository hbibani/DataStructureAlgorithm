#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <list>
#include <iterator>
using namespace std;

#include "state.h"

int main()
{
	srand(time(0));
	State state;
	state.printBoard();
	state.pushDown();
	state.printBoard();
	return 0;
}
