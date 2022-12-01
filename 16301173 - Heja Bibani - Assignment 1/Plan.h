#ifndef Plan_h
#define Plan_h



class Plan : public Action
{
protected:
	priority_queue< Action > threeNine;
	vector< positionsAvailable > posAvailable;
	vector< positionsTop > posTops;
	vector< Action > tekashi69or99;
	vector< State > usedStates;
	vector< int> blockNumberUsed;
	int totalAmountOfSteps;

public:

	void generateAvailablePositions(State state)
	{
		state.availablePositions(posAvailable);
	}
	
    
	virtual void generateTopPositions()
	{
		
	}
	

	virtual void playerTypeGeneric()
	{

	}


	virtual void generateAvailableActions()
	{

	}
	

};



class conjunctiveGameAttack1 : public Plan
{

public:

	void generateTopPositions(State state)
	{
		state.topValues(posTops, blockNumberUsed); //excludes goals which have been attained
	}

	void generateAvailablePositions(State state)
	{
		state.availablePositions(posAvailable);
	}

	void  generateAvailableActions(State* state, priority_queue< Goal >& goals)
	{
		generateAvailablePositions(*state); //working n^2
		generateTopPositions(*state); //working   n^2
		int sizeAv = posAvailable.size();
		int sizeTop = posTops.size();

		for (int i = sizeTop - 1; i >= 0; i--)
		{
			for (int j = sizeAv - 1; j >= 0; j--)

				if (!(posAvailable[j].colAv == posTops[i].colTop))
				{
					Action mp;
					mp.blockNumberAct = posTops[i].blockNumber;
					mp.goalNumberAct = goals.top().number;
					mp.rowFrom = posTops[i].rowTop;
					mp.colFrom = posTops[i].colTop;
					mp.rowTo = posAvailable[j].rowAv;
					mp.colTo = posAvailable[j].colAv;
					mp.generateHeuristicValue(&(*state), goals.top());
					threeNine.push(mp);
				}
		}

	}

	void planTypeGeneric(State* state, priority_queue< Goal >& goals)
	{
		totalAmountOfSteps = 0;
		cout << "Conjunctive " << endl;
		int randomNumberRowTo = 0;
		int randomNumberColTo = 0;
		bool testDangerPosition = false;
		int test = 0;

		for (int i = 0; i < 100; i++)
		{
			State stateTest(state->getRows());
			//stateTest.setBoard(state.getRows());
			stateTest = *state;
			if (i == 0)
			{
				usedStates.push_back(stateTest);
			}
			int rowFrom = 0;
			int colFrom = 0;
			int blockNumber = goals.top().number;
			state->getBlockCurrentRowCol(blockNumber, rowFrom, colFrom);
			int testForUsed = 0;
			generateAvailableActions(&stateTest, goals);


			while (threeNine.size() > 0)
			{
				test = 0;
				Action second;
				second = threeNine.top();
				threeNine.pop();

				if (second.heuristicValue == 100)
				{
					cout << "Goal found  , ( " << goals.top().number << ", " << goals.top().row << ", " << goals.top().col << ")" << endl;
					second.makeMove(stateTest);
					*state = stateTest;
					blockNumberUsed.push_back(goals.top().number);

					while (!usedStates.empty())
					{
						usedStates.back().destroyBoard();
						usedStates.pop_back();
					}


					goals.pop();
				}
				else if (second.heuristicValue < 100)
				{
					second.makeMove(stateTest);

					for (unsigned int j = 0; j < usedStates.size(); j++)
					{
						if (usedStates[j] == stateTest)
						{
							test = 1;
							stateTest = *state;
							break;
						}
					}
				}

				if (test == 0)
				{
					second.printMove();
					*state = stateTest;
					usedStates.push_back(stateTest);
					totalAmountOfSteps++;
					state->displayBoard();
					break;
				}
			}

			while (!threeNine.empty())
			{
				threeNine.pop();
			}

			while (!posAvailable.empty())
			{
				posAvailable.pop_back();
			}

			while (!posTops.empty())
			{
				posTops.pop_back();
			}

			if (goals.empty())
			{
				break;
			}

			if (goals.empty())
			{
				stateTest.destroyBoard();
				break;

			}

		}

		cout << "Completed in " << totalAmountOfSteps << " steps.";

		if (goals.size() > 0)
		{
			while (!usedStates.empty())
			{
				usedStates.back().destroyBoard();
				usedStates.pop_back();
			}
		}
	}

};



class conjunctiveGameAttack : public Plan
{

public:

	void generateTopPositions(State state)
	{
		state.topValues(posTops, blockNumberUsed); //excludes goals which have been attained
	}

	void  generateAvailableActions(State state, priority_queue< Goal >& goals)
	{
		generateAvailablePositions(state); 			//9n^2 + 9n + 1
		generateTopPositions(state); 				//11n^2 + 7n + 1
		int sizeAv = posAvailable.size();			
		int sizeTop = posTops.size();

		for (int i = sizeTop - 1; i >= 0; i--) //n^2
		{
			for (int j = sizeAv - 1; j >= 0; j--)

				if (!(posAvailable[j].colAv == posTops[i].colTop)) //n^2 - n
				{
					Action mp;
					mp.blockNumberAct = posTops[i].blockNumber;
					mp.goalNumberAct = goals.top().number;
					mp.rowFrom = posTops[i].rowTop;
					mp.colFrom = posTops[i].colTop;
					mp.rowTo = posAvailable[j].rowAv;
					mp.colTo = posAvailable[j].colAv;
					mp.generateHeuristicValue(&state, goals.top());
					threeNine.push(mp); 
				}
		}

	}

	bool testIfBottomAndOpen(State* state, int blockNumber, int currentRow, priority_queue< Goal >& goals)
	{
		if (state->isBlockNumberTop(blockNumber) && currentRow == (state->getRows() - 1)) //3n^2 + 4n + 20
		{
			while (threeNine.top().blockNumberAct != blockNumber) //1
			{
				if (threeNine.top().blockNumberAct != blockNumber) //n^2logn - nlogn
				{
					threeNine.pop(); 
				}
			}

			Action first = threeNine.top(); //1
			first.makeMove(*state); //3n^2+3n+7
			first.printMove();      //19

			if (first.heuristicValue == 100)
			{
				cout << "Goal found  , ( " << goals.top().number << ", " << goals.top().row << ", " << goals.top().col << ")" << endl; //9
				blockNumberUsed.push_back(goals.top().number); //1
				state->displayBoard(); //4n^2 + 8n + 3

				while (!usedStates.empty())
				{
					usedStates.back().destroyBoard();
					usedStates.pop_back();
				}


				goals.pop();

				return true;
			}

			while (!threeNine.empty())
			{
				threeNine.pop(); //n^2logn - nlogn
			}

			while (!posAvailable.empty())
			{
				posAvailable.pop_back(); //n
			}

			while (!posTops.empty())
			{
				posTops.pop_back(); //n
			}


			int colFrom = 0;
			generateAvailableActions(*state, goals); //9n^4 + 55n^2 + n^2logn - 20n - nlogn
			state->displayBoard(); ////4n^2 + 8n + 3
			state->getBlockCurrentRowCol(blockNumber, rowFrom, colFrom); //3n^2 + 3n+ 3


			//gets rid of actions which are block numbers [force a move on some other piece]
			while (threeNine.top().blockNumberAct == blockNumber || (threeNine.top().blockNumberAct != blockNumber && threeNine.top().colTo == colFrom))
			{
				threeNine.pop(); //5n + n^2logn - nlogn
			}

			Action second = threeNine.top(); //6
			second.makeMove(*state); //3n^2+3n+7
			second.printMove(); //19
			state->displayBoard(); //4n^2 + 8n + 3

			while (!threeNine.empty())
			{
				threeNine.pop(); //n^2logn - nlogn
			}


			while (!posAvailable.empty())
			{
				posAvailable.pop_back(); //n
			}

			while (!posTops.empty())
			{
				posTops.pop_back(); //n
			}


			return true; //1
		}
		else
		{
			return false;
		}
	}

	void planTypeGeneric(State* state, priority_queue< Goal >& goals)
	{
		totalAmountOfSteps = 0; //1
		//	cout << "Conjunctive " << endl;
		int randomNumberRowTo = 0; //1
		int randomNumberColTo = 0; //1
		int test = 0; //1
		bool testDangerPosition; //1
		
		int used;
		

		for (int i = 0; i < 100; i++)
		{
			State stateTest(state->getRows());  //1
			stateTest = *state;     //3n^2 + 3n + 3
			testDangerPosition = false; //1
			if (i == 0)
			{
				usedStates.push_back(stateTest); //1
				used++;
			}
			int rowFrom = 0; //1
			int colFrom = 0; //1
			int blockNumber = goals.top().number; //1
			stateTest.getBlockCurrentRowCol(blockNumber, rowFrom, colFrom); //3n^2 + 3n+ 3	
			int testForUsed = 0; //1
			generateAvailableActions(stateTest, goals); //9n^4 + 55n^2 + n^2logn - 20n - nlogn

			testDangerPosition = testIfBottomAndOpen(&stateTest, blockNumber, rowFrom, goals); 
			used++;
			
			if (testDangerPosition == true)
			{
				*state = stateTest; //3n^2 + 3n + 3
					used++;
			}
			else
			{
				while (threeNine.size() > 0) //n^2 - n
				{
					test = 0;
					Action second;
					second = threeNine.top();
					threeNine.pop();

					if (second.heuristicValue == 100)
					{
						cout << "Goal found  , ( " << goals.top().number << ", " << goals.top().row << ", " << goals.top().col << ")" << endl; //8
						second.makeMove(stateTest); 							//1
						*state = stateTest; 									//3n^2 + 3n + 3
						blockNumberUsed.push_back(goals.top().number); 			//1
						used++;
						while (!usedStates.empty()) 
						{
							usedStates.back().destroyBoard();
							usedStates.pop_back();
							used++;
						}

						goals.pop();

					}
					else if (second.heuristicValue < 100) // n
					{
						second.makeMove(stateTest); //3n^2 + 3n + 7

						for (unsigned int j = 0; j < usedStates.size(); j++) //300
						{
							if (usedStates[j] == stateTest)
							{
								test = 1;
								stateTest = *state; // 3n^2 + 3n + 3
								used++;
								break;
							}
							used++;
						}
					}

					if (test == 0)
					{
						second.printMove();  //19
						*state = stateTest; // 3n^2 + 3n + 3
						usedStates.push_back(stateTest); //1
						totalAmountOfSteps++;
						state->displayBoard(); //4n^2 + 8n + 3
						used++;
						break;
					}
				}
			}

			while (!threeNine.empty()) //logn(n^2-n)
			{
				threeNine.pop(); 
				used++;
			}

			while (!posAvailable.empty()) //n(2)
			{
				posAvailable.pop_back();
				used++;
			}

			while (!posTops.empty()) //n(2)
			{
				posTops.pop_back();
				used++;
			}

			
			if (goals.empty())
			{
				stateTest.destroyBoard();
				break;
				used++;

			}
			
		}
		cout << "Completed in " << totalAmountOfSteps << " steps.";
		cout << endl << "Number used: " << used <<endl;

		if (goals.size() > 0)
		{
			while (!usedStates.empty())
			{
				usedStates.back().destroyBoard();
				usedStates.pop_back();
			}
		}
		
	}

};


class disjunctiveGameAttack : public Plan
{
public:
	void generateTopPositions(State state)
	{
		state.topValuesDisjunctive(posTops);
	}

	void generateAvailableActions(State state, list< Goal >& goals)
	{
		generateAvailablePositions(state);//working
		generateTopPositions(state); //working
		int sizeAv = posAvailable.size();
		int sizeTop = posTops.size();

		for (int i = sizeTop - 1; i >= 0; i--)
		{
			for (int j = sizeAv - 1; j >= 0; j--)

				if (!(posAvailable[j].colAv == posTops[i].colTop))
				{
					Action mp;
					mp.blockNumberAct = posTops[i].blockNumber;
					mp.goalNumberAct = goals.front().number;
					mp.rowFrom = posTops[i].rowTop;
					mp.colFrom = posTops[i].colTop;
					mp.rowTo = posAvailable[j].rowAv;
					mp.colTo = posAvailable[j].colAv;
					mp.generateHeuristicValue(&state, goals.front());
					threeNine.push(mp);
				}
		}
	}

	void planTypeGeneric(State* state, list< Goal >& goals) //non-Conjunctive
	{
		cout << "disjunctive" << endl;
		int randomNumberRowTo = 0;
		int randomNumberColTo = 0;
		bool testDangerPosition = false;
		int test = 0;
		totalAmountOfSteps = 0;

		for (int i = 0; i < 100; i++)
		{
			
			State stateTest(state->getRows());  //n^2
			stateTest = *state; // n^2
			int rowFrom = 0;
			int colFrom = 0;
			if (i == 0)
			{
				usedStates.push_back(stateTest);
			}
			int blockNumber = goals.front().number;
			state->getBlockCurrentRowCol(blockNumber, rowFrom, colFrom); //n^2
			generateAvailableActions(stateTest, goals); //3n^2

			while (threeNine.size() > 0)
			{
				test = 0;
				Action second;
				second = threeNine.top();
				threeNine.pop();

				if (second.heuristicValue == 100)
				{
					cout << "Goal found  , ( " << goals.front().number << ", " << goals.front().row << ", " << goals.front().col << ")" << endl;
					second.makeMove(*state);
					goals.pop_front();
					second.printMove();

					while (!usedStates.empty())
					{
						usedStates.back().destroyBoard();
						usedStates.pop_back();
					}


					break;
				}
				else if (second.heuristicValue < 100)
				{
					second.makeMove(stateTest);

					for (unsigned int j = 0; j < usedStates.size(); j++)
					{
						if (usedStates[j] == stateTest)
						{
							test = 1;
							stateTest = *state;
							break;
						}
					}
				}

				if (test == 0)
				{
					second.printMove();
					*state = stateTest; //n^2
					usedStates.push_back(stateTest);
					state->displayBoard(); //n^2
					cout << endl << endl;
					
					break;
				}
			}

			while (!threeNine.empty())
			{
				threeNine.pop();
			}

			while (!posAvailable.empty())
			{
				posAvailable.pop_back();
			}

			while (!posTops.empty())
			{
				posTops.pop_back();
			}

			if (goals.empty())
			{
				stateTest.destroyBoard();
				break;
			}

			if (goals.size() == 0)
			{
				break;
			}
			
			totalAmountOfSteps++;
		}

		state->displayBoard(); //n^2
		cout << "Completed in " << totalAmountOfSteps << " steps.";
		if (goals.size() > 0)
		{
			while (!usedStates.empty())
			{
				usedStates.back().destroyBoard();
				usedStates.pop_back();
			}
		}
	}
};





class threeStatesGameAttack : public Plan
{
	void generateTopPositions(State state)
	{
		state.topValuesDisjunctive(posTops);
	}

	void generateAvailableActions(State state, Goal goals)
	{
		generateAvailablePositions(state); //working
		generateTopPositions(state); //working
		int sizeAv = posAvailable.size();
		int sizeTop = posTops.size();

		for (int i = sizeTop - 1; i >= 0; i--)
		{
			for (int j = sizeAv - 1; j >= 0; j--)

				if (!(posAvailable[j].colAv == posTops[i].colTop))
				{
					Action mp;
					mp.blockNumberAct = posTops[i].blockNumber;
					mp.goalNumberAct = goals.number;
					mp.rowFrom = posTops[i].rowTop;
					mp.colFrom = posTops[i].colTop;
					mp.rowTo = posAvailable[j].rowAv;
					mp.colTo = posAvailable[j].colAv;
					mp.generateHeuristicValue(state, goals);
					threeNine.push(mp);
				}
		}

	}

public:
	void displayBoardStorage(vector< State > storage)
	{
		for (int i = 0; i < storage.size(); i++)
		{
			storage[i].displayBoard();
		}
	}

	int tekashi99Venom(State& state, Goal goal, vector< State >& storage)
	{

		for (int i = 0; i < 3; i++)
		{
			State storageTest(state.getRows());
			//storageTest.setBoard(state.getRows());

			int rowFrom = 0;
			int colFrom = 0;
			int blockNumber = goal.number;
			state.getBlockCurrentRowCol(blockNumber, rowFrom, colFrom); //working
			generateAvailablePositions(state); //working
			generateTopPositions(state); //working

			bool testDangerPosition = state.dangerPositionAvailable(blockNumber, rowFrom, colFrom, goal);

			if (testDangerPosition == true)
			{
				cout << "Goal found  , ( " << blockNumber << ", " << goal.row << ", " << goal.col << ")";
				cout << endl;
				storageTest = state;
				storage.push_back(storageTest);
				return 1;
			}

			//need to implement, if blockNumber is top AND blockNumber is not in the same column as the goal, switch to function which tries to free the space of the goal

			int sizeAv = posAvailable.size();
			int sizeTop = posTops.size();
			generateAvailableActions(state, goal);


			for (int i = sizeTop - 1; i >= 0; i--)
			{
				for (int j = sizeAv - 1; j >= 0; j--)
				{
					if (!(posAvailable[j].colAv == posTops[i].colTop))
					{
						Action mp;
						mp.blockNumberAct = posTops[i].blockNumber;
						mp.goalNumberAct = goal.number;
						mp.rowFrom = posTops[i].rowTop;
						mp.colFrom = posTops[i].colTop;
						mp.rowTo = posAvailable[j].rowAv;
						mp.colTo = posAvailable[j].colAv;
						mp.generateHeuristicValue(state, goal);
						tekashi69or99.push_back(mp);
					}
				}
			}

			for (int i = 0; i < tekashi69or99.size(); i++)
			{
				if (tekashi69or99[i].heuristicValue == 99)
				{
					tekashi69or99[i].makeMove(state);
					storageTest = state;
					storage.push_back(storageTest);
					return 2;
				}
			}

			if (tekashi69or99.size() > 0)
			{
				int randomNumberTekashi = rand() % tekashi69or99.size();
				tekashi69or99[randomNumberTekashi].makeMove(state);
				storageTest = state;
				storage.push_back(storageTest);
			}

			while (!tekashi69or99.empty())
			{
				tekashi69or99.pop_back();
			}

			while (!posAvailable.empty())
			{
				posAvailable.pop_back();
			}

			while (!posTops.empty())
			{
				posTops.pop_back();
			}

		}

		return 3;

	}

	void planTypeGeneric(State& state, list< Goal >& goals)
	{

		for (int i = 0; i < 40; i++)
		{
			vector < State > stateVector;

			int whichStorage = 0;
			int isGoalAchieved = 0;
			int goalAchieved[3];

			vector< State > storage1;
			vector< State > storage2;
			vector< State > storage3;

			state.displayBoard();

			for (int j = 0; j < 3; j++)
			{
				State state1(state.getRows());
				//state1.setBoard(state.getRows());
				state1 = state;
				stateVector.push_back(state1);
			}

			for (int j = 0; j < 3; j++)
			{
				goalAchieved[j] = 0;
			}

			int totalGoals = goals.size();

			if (totalGoals > 0)
			{
				goalAchieved[0] = tekashi99Venom(stateVector[0], goals.front(), storage1);
				goalAchieved[1] = tekashi99Venom(stateVector[1], goals.front(), storage2);
				goalAchieved[2] = tekashi99Venom(stateVector[2], goals.front(), storage3);
			}

			int testIfThereIsAgoal = 0;


			for (int j = 0; j < 3; j++) // scan if goal has been achieved
			{
				if (goalAchieved[j] == 1)
				{
					testIfThereIsAgoal++;
					goals.pop_back();
					isGoalAchieved = 1;
					whichStorage = j;
					break;
				}
			}


			if (isGoalAchieved == 0)
			{
				for (int j = 0; j < 3; j++)  //scan if there is a heuristic value 99;
				{
					if (goalAchieved[j] == 2)
					{
						testIfThereIsAgoal++;
						whichStorage = j;
						break;
					}
				}

				if (testIfThereIsAgoal == 0)
				{
					int randomNumberChooseIfNo1 = rand() % 3;
					whichStorage = randomNumberChooseIfNo1;
				}
			}

			State s(state.getRows());
			//s.setBoard(state.getRows());


			switch (whichStorage) //print the states which were chosen
			{
			case 0:
				displayBoardStorage(storage1);
				s = storage1[storage1.size() - 1];
				state = s;
				break;
			case 1:
				displayBoardStorage(storage2);
				s = storage2[storage2.size() - 1];
				state = s;
				break;
			case 2:
				displayBoardStorage(storage3);
				s = storage3[storage3.size() - 1];
				state = s;
				break;
			default:
				cout << "working.";
			}


			while (!storage1.empty())
			{
				storage1.pop_back();
			}

			while (!storage2.empty())
			{
				storage2.pop_back();
			}

			while (!storage3.empty())
			{
				storage3.pop_back();
			}

			if (isGoalAchieved == 1)
			{
				break;
			}
		}
 };



#endif
