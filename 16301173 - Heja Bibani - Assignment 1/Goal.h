#ifndef Goal_h
#define Goal_h

class Goal
{
public:
	int number;
	int row;
	int col;

	Goal()
	{

	}

	Goal(int num, int r, int c)
	{
		number = num;
		row = r;
		col = c;
		cout << "A block has been added, (Number = " << num << ", Row = " << row << ", Col = " << col << " )" << endl << endl;
	}

	bool operator <(const Goal g) const
	{
		if (row < g.row)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator>(const Goal g) const
	{
		if (row > g.row)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};



#endif 