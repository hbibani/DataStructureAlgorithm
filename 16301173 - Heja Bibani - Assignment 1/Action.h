#ifndef Action_h
#define Action_h


class Action
{
public:
	int heuristicValue;
	int rowTo;
	int colTo;
	int rowFrom;
	int colFrom;
	int blockNumberAct;
	int goalNumberAct;
	int goalRow;
	int goalCol;


	Action()
	{
		int heuristicValue = 0;
		int rowTo = 0;
		int colTo = 0;
		int rowFrom = 0;
		int colFrom = 0;
		int blockNumberAct = 0;
	}

	void generateHeuristicValue(State* states, Goal goal)
	{
		//need to make ghost
		int r;
		r = states->getRows();
		State stateGhost(r);
		stateGhost = *states;
		stateGhost.getMoveThenMakeMove(blockNumberAct, rowTo, colTo);
		heuristicValue = stateGhost.getHeuristicValue(goal);
		stateGhost.destroyBoard();
	}


	void makeMove(State& states)
	{
		states.getMoveThenMakeMove(blockNumberAct, rowTo, colTo);
	}


	void printMove()
	{
		cout << "Making Move: " << blockNumberAct << "( rowFrom: " << rowFrom << ", colFrom: " << colFrom << " )"
			<< endl << "Moving to: ( rowTo: " << rowTo << ", colTo: " << colTo << " )" << endl << endl;
		cout << "Heuristic Value: " << heuristicValue << endl << endl;
	}

	void operator =(Action a)
	{
		heuristicValue = a.heuristicValue;
		rowTo = a.rowTo;
		colTo = a.colTo;
		rowFrom = a.rowFrom;
		colFrom = a.colFrom;
		blockNumberAct = a.blockNumberAct;
	}

	bool operator <(const Action a) const
	{
		if (heuristicValue < a.heuristicValue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator ==(const Action a) const
	{
		if (heuristicValue == a.heuristicValue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator >(const Action a) const
	{
		if (heuristicValue > a.heuristicValue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	~Action()
	{

	}
};

#endif
