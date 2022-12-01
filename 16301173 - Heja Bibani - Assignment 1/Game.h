
#ifndef Game_h
#define Game_h

class Game
{

public:

	void getGoals()  //gets goals
	{
		int test = 1;
		int testtest = 1;
		int number;
		int row;
		int col;
		int testTheNumber = 0;
		int checkAgain = 0;
		totalGoals = 0;

		while (test == 1)
		{
			cout << "Pick a number between 0 and " << ((sizeBoard * sizeBoard) - sizeBoard) << ":" << endl;
			cin >> number;
			cout << endl;
			checkNumber(number, 0);
			cout << "Enter a row number between 0 and " << sizeBoard - 1 << ":" << endl;
			cin >> row;
			checkNumber(row, 1); 
			cout << endl;
			cout << "Enter a col number between 0 and " << sizeBoard - 1 << ":" << endl;
			cin >> col;
			checkNumber(col, 1);
			cout << endl;

			if (isDiffGoal(number) == true)
			{
				Goal goalAdd(number, row, col);
				numberUsed.push_back(number);

				if (typeOfGame == 1)
				{
					conjunctiveGoalChecker.push(goalAdd);
				}
				else if (typeOfGame == 0)
				{
					goalQue.push_back(goalAdd);
				}

			}
			else
			{
				cout << "Sorry this value has been covered.";
				cout << endl;
			}

			cout << "Would you like to add another goal, 0 for No, 1 for yes?";
			cout << endl;
			cin >> testtest;
			cout << endl;
			checkNumber(testtest, 2);
			test = testtest;
		}
	}


	void startGame()
	{
		int testGame = 0;
		getGoals();

		if (typeOfGame == 1)
		{
			conjunc.planTypeGeneric(states, conjunctiveGoalChecker);
		}
		else
		{
			disjunc1.planTypeGeneric(states, goalQue);  //this is 3 state move maker; 3 levels deep
		}

	//	states->destroyBoard();

		//planner.threeNinesMoveMaker( states , goalQue , totalGoals ); //heuristic excessive calculation
		//planner.tekashi69Venom( states , goalQue , totalGoals , conjunctiveGoalChecker );
		//planner.tekashi99Venom( states , goalQue , totalGoals , conjunctiveGoalChecker );
		//planner.make3Moves( states, goalQue );  //this is 3 state move maker; 3 levels deep
	}


	//working checks to see if a goal has been picked
	bool isDiffGoal(int valuePicked)
	{
		if (numberUsed.empty())
		{
			return true;
		}

		for (unsigned int i = 0; i < numberUsed.size(); i++)
		{
			if (valuePicked == numberUsed[i])
			{
				return false;
			}
		}

		return true;
	}


	void checkNumber(int& numberToTest, int type) //type is depending on whether it is a col/row or the number out of the list to test
	{

		if (type == 0)
		{
			while (numberToTest < 1 || numberToTest >((sizeBoard * sizeBoard) - sizeBoard))
			{
				cout << "That was an invalid choice, could you please enter a number through the range specified.";
				cin >> numberToTest;
				cout << endl;
			}
		}

		if (type == 1)
		{
			while (numberToTest < 0 || numberToTest > sizeBoard - 1)
			{
				cout << "That was an invalid choice, could you please enter a number through the range specified.";
				cin >> numberToTest;
				cout << endl;
			}
		}


		if (type == 2)
		{
			while (numberToTest < 0 || numberToTest  > 1)
			{
				cout << "That was an invalid choice, could please pick 1 for yes, and 0 for no.";
				cin >> numberToTest;
				cout << endl;
			}
		}

		if (type == 3)
		{
			while (numberToTest < 0 || numberToTest > 1)
			{
				cout << "Sorry that was an invalid choice, please pick 0 for disjunctive or 1 for conjunctive";
				cin >> numberToTest;
				cout << endl;
			}
		}
	}

	Game()
	{
		typeOfGame = 0;
		cout << "Press 0 for disjunctive game, or  1 for conjunctive game:" << endl;
		cin >> typeOfGame;
		checkNumber(typeOfGame, 3);
		cout << endl;
		cout << "Enter Size of Board" << endl;
		cin >> sizeBoard;
		cout << endl;
		states = new State(sizeBoard);
		states->genInitialState();
		states->displayBoard();
	}

	~Game()
	{
		delete states;
	}

private:
	int sizeBoard;
	int totalGoals;
	list< Goal > goalQue;
	priority_queue< Goal > conjunctiveGoalChecker;
	vector< int > numberUsed;
	State* states;
	conjunctiveGameAttack conjunc;
	disjunctiveGameAttack disjunc1;
	vector< Action > tekashi69or99;
	priority_queue< Action > threeNine;
	int typeOfGame;
};

#endif
