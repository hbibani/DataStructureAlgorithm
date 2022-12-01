#ifndef IdeaBank_h
#define IdeaBank_h
//task 7 to complete
class ideaBank
{
private:
	vector< Idea > ideaObj;
	Index index;
	AvlTree< Index , string > iDAVLTree;
	vector< string > keyWordsVec;
	int IdToDelete;

public:
	void driver( );
	void deletePrompt( );
	void queryPrompt( );
	void queryOr( string keyWord1 , string keyWord2 );  //bonus 8.1
	void queryAnd( string keyWord1 , string keyWord2 ); //bonus 8.2
	void query( string keyWord );		//task 6.2 
	void lookForWordIdeas( string word ); //task 6.1
	void indexAlg( );				//task 5 [look at AVL tree for more information]
	void inputIdea( );				//task 3.1
	void deleteIdea( int ID );		//task 3.3
	void displayIdeas( );			//task 3.4 - display all ideas
	void displayOneIdea( int ID );	//task 3.2 -display one idea
	void inputFromText( );			//task 4
	bool checkDuplicates(Idea Id);
	int binarySearch(int target);
	void binarySearchPrompt();
};

void ideaBank::driver( )
{

	bool test = true;
	string y;

	do
	{
		cout << "Pick what you want to do." << endl;
		cout << "(1) Input from file" << endl;
		cout << "(2) Index algorithm" << endl;
		cout << "(3) Display ideas" << endl;
		cout << "(4) Make a query" << endl;
		cout << "(5) Input Idea" << endl;
		cout << "(6) Delete Idea" << endl;
		cout << "(7) Search Idea [binary search]" << endl;
		cout << "(8) Exit" << endl;
		cout << endl;
		getline(cin, y);
		int x = stoi(y);
		switch (x)
		{
			case 1:
				inputFromText();
				break;
			case 2: 
				indexAlg();
				break;
			case 3: 
				displayIdeas();
				break;
			case 4:
				queryPrompt();
				break;
			case 5: 
				inputIdea();
				break;
			case 6: 
				deletePrompt();
				break;
			case 7:
				binarySearchPrompt();
				break;
			case 8:
				test = false;
				break;	
		}
	} while( test == true ) ;

}

void ideaBank::deletePrompt( )
{	
	int ID;
	string number;
	cout << "Enter an id you want to delete, or enter -1 for nothing";
	cout << endl;
	getline(cin, number);
	ID = stoi(number);
	if ( ID > 0 )
	{
	  deleteIdea( ID );
	}

}

void ideaBank::queryPrompt()
{
	string query1;
	cout << "Enter a query, or press n to exit:" << endl;
	if (query1 == "n")
	{
		return;
	}
	cout << endl;
	getline(cin, query1);
	query(query1);
}

void ideaBank::queryOr(string keyWord1, string keyWord2)
{
	Index indexBuffer1;
	Index indexBuffer2;
	list<int> commonNumbers;
	bool test1 = iDAVLTree.AVL_RetrieveV2(keyWord1, indexBuffer1); //check to see if it is contained
	bool test2 = iDAVLTree.AVL_RetrieveV2(keyWord2, indexBuffer2); //check to see if it is contained

	if ( test1 == true )
	{
		for (int i = 0; i < indexBuffer1.idList.size(); i++)
		{
			commonNumbers.push_back(indexBuffer1.idList[i]); //push all the ids into array
		}
	}

	if ( test2 == true )
	{
		//push the ones which are not common onto the vector
		for (int j = 0; j < indexBuffer2.idList.size(); j++)
		{
			bool test = true;
			list<int>::iterator it;
			for (it = commonNumbers.begin(); it != commonNumbers.end(); it++)
			{
				if (indexBuffer2.idList[j] == *it)
				{
					test = false;
				}
			}
			
			if (test == true)
			{
				commonNumbers.push_back(indexBuffer2.idList[j]);
			}
		}
	}

	if (test2 == true || test1 == true)
	{
		//commonNumbers.unique();
		commonNumbers.sort();
		cout << "Key word[disjunctive]: " << keyWord1 << " " << keyWord2;
		cout << endl;
		cout << "Matches [ids] : ";
		list<int>::iterator it;

		for (it = commonNumbers.begin(); it != commonNumbers.end(); it++)
		{
			cout << *it << " ";
			cout << endl;
		}
		cout << endl << endl;
	}
	else
	{
		cout << "No entry matching request..." << endl;
	}
}

//q7a
void ideaBank::queryAnd( string keyWord1 , string keyWord2 )
{
	Index indexBuffer1;
	Index indexBuffer2;
	vector< int > commonNumbers;
	bool test1 = iDAVLTree.AVL_RetrieveV2(keyWord1, indexBuffer1); //check if query1 is in tree
	bool test2 = iDAVLTree.AVL_RetrieveV2(keyWord2, indexBuffer2); //check if query2 is in the tree

	if ( test1 == true && test2 == true )
	{
		for ( int i = 0; i < indexBuffer1.idList.size(); i++ )
		{
			for ( int j = 0; j < indexBuffer2.idList.size( ); j++ )
			{
				if ( indexBuffer1.idList[i] == indexBuffer2.idList[j] )
				{
					commonNumbers.push_back(indexBuffer1.idList[i]);
				}
			}
		}

		cout << "Key word[Conjunctive]: " << keyWord1 << " " << keyWord2;
		cout << endl;
		cout << "Matches [ids] : ";

		for (int i = 0; i < commonNumbers.size(); i++)
		{
			cout << commonNumbers[i] << " ";
		}
		cout << endl << endl;
	}
	else
	{
		cout << "No entry matching request..." << endl;
	}
}

//question 6b
void ideaBank::query(string keyWord) 
{
	vector<string> storage;
	string intermediate;
	stringstream ss(keyWord);

	//remove all ","
	char chars[] = ".,;'[]{}";
	while (getline(ss, intermediate, ' '))
	{
		for (int i = 0; i < strlen(chars); i++)
		{
			intermediate.erase(remove(intermediate.begin(), intermediate.end(), chars[i]), intermediate.end());
		}
		
		storage.push_back(intermediate);
	}
   
	if (storage.size() == 1)
	{
		Index indexBuffer; //create buffer
		if (iDAVLTree.AVL_RetrieveV2(keyWord, indexBuffer) == true)
		{
			cout << "Key word: " << keyWord;
			cout << endl;
			cout << "Matches [ids] : ";
			for (int i = 0; i < indexBuffer.idList.size(); i++)
			{
				cout << indexBuffer.idList[i] << " ";
			}

			cout << endl << endl;
		}
		else
		{
			cout << "No entry matching request..." << endl;
		}
	}

	if (storage.size() > 1)
	{
		if (storage[1] == "AND")
		{
			queryAnd(storage[0], storage[2]);
		}

		if (storage[1] == "OR")
		{
			queryOr(storage[0], storage[2]);
		}
	}
}


//Question 6a
void ideaBank::lookForWordIdeas(string word)
{
	cout << "Looking for string [ideas]: " << word;
	cout << endl;
	for (int i = 0; i < ideaObj.size(); i++)
	{
		if (ideaObj[i].checkKeyContentsIdeaSearch(word))
		{
			cout << "Found in ID: " << ideaObj[i].ID;
			cout << endl;
			
		}
	}

	cout << endl << endl;
}

void ideaBank::indexAlg()
{
	string theKeyWord;

	int idPush;

	for (int i = 0; i < ideaObj.size(); i++)
	{
		ideaObj[i].addKeyWordToVector(keyWordsVec);
		ideaObj[i].addContentTokenizeToVect(keyWordsVec);
	}

	for (int i = 0; i < keyWordsVec.size(); i++)
	{
		Index Structure;
		Structure.key = keyWordsVec[i];
		// traverse through ideas
		for (int j = 0; j < ideaObj.size(); j++)
		{
			if ( ideaObj[j].checkKeyWordVector(keyWordsVec[i]) || ideaObj[j].checkContent(keyWordsVec[i]) )
			{
				Structure.idList.push_back(ideaObj[j].ID);
			}
		}

		iDAVLTree.AVL_InsertV2(Structure);
	}
}

void ideaBank::inputIdea()
{
	string prop;
	string cont;
	string keyWord;
	bool exit = false;

	cout << " Enter a new idea " << endl;
	cout << endl;
	cout << " Enter proposer name: ";
	getline(cin, prop);
	cout << endl;
	cout << " Enter content name: ";
	getline(cin, cont);
	Idea idea(prop, cont);
	cout << endl;
	bool test = true;
	int initialSize = keyWordsVec.size() - 1;
	int amount = 0;
	while (test == true)
	{
		cout << " Enter a keyword, press n to stop : ";
		getline(cin, keyWord);
		cout << "Key word: " << keyWord << endl;

		if (keyWord == "n" || keyWord == "N")
		{
			test = false;
		}
		else
		{
			idea.addKeyWord(keyWord);
			amount++;
		}
	}


	ideaObj.push_back(idea);
	indexAlg();
}


// this gets the corresponding ID number; checks the ids that are held in the vector and deletes it, then deletes all the entries with that id in the AVL_TREE
void ideaBank::deleteIdea( int ID )
{
	bool test = true;
	vector<string> keyWords;
	
	for (int i = 0; i < ideaObj.size(); i++)
	{
		if (ID == ideaObj[i].ID)
		{
			keyWords = ideaObj[i].getKeyWord();
			ideaObj.erase(ideaObj.begin() + i);
			test = true;
		}
	}

	for (int i = 0; i < keyWords.size(); i++)
	{
		Index indexBuffer; //set buffer
		iDAVLTree.AVL_RetrieveV2(keyWords[i], indexBuffer); //retrieve buffer
		
		//find the values inside the buffer
		for (int j = 0; j < indexBuffer.idList.size(); j++)
		{
			if (indexBuffer.idList[j] == ID)
			{
				indexBuffer.idList.erase(indexBuffer.idList.begin() + j);
			}
		}

		if (indexBuffer.idList.size() == 0)
		{
			iDAVLTree.AVL_Delete(keyWords[i]);
		}
		else
		{
			iDAVLTree.AVL_Update(keyWords[i], indexBuffer);
		}
	}


	if (test == true)
	{
		cout <<"ItemID:" << ID  << " Item has been deleted." << endl << endl;
	}
	else
	{
		cout << "ItemID:" << ID << " Item was not found...." << endl << endl;
	}
}

void ideaBank::displayIdeas()
{
	bool test = true;

	if (ideaObj.size() == 0)
	{
		cout << "No ideas in here." << endl;
		test = false;
	}

	if (test == true)
	{
		for (int i = 0; i < ideaObj.size(); i++)
		{
			ideaObj[i].printIdeaContent();
			cout << endl << endl;
		}
	}
}

void ideaBank::displayOneIdea(int ID)
{
	bool test = true;
	bool objectIn = false;

	if (ideaObj.size() == 0)
	{
		cout << "No ideas in here..." << endl << endl;
		test = false;
	}

	if (test == true)
	{
		for (int i = 0; i < ideaObj.size(); i++)
		{
			if (ideaObj[i].ID == ID)
			{
				ideaObj[i].printIdeaContent();
				cout << endl << endl;
				objectIn == true;
				break;
			}
		}
	}

	if (objectIn == false)
	{
		cout << "The object was not in here." << endl;
		cout << endl;
	}
}

void ideaBank::inputFromText()
{
	string line;
	ifstream file;
	file.open("ideas.txt");

	if (file.fail()) {
		cout << "Failed to open file" << endl;
		exit(1);
	}

	int count = 1;
	string content;
	string prop;

	while (!file.eof())
	{
		vector <string> tokens;
		string intermediate;
		getline(file, line);
		stringstream check1(line);
		while (getline(check1, intermediate, ' '))
		{
			tokens.push_back(intermediate);
		}
		
			if (line != "")
			{
				if (count == 1)
				{
					stringstream ss1;
					for (int i = 1; i < tokens.size(); i++)
					{
						ss1 << tokens[i];
						ss1 << " ";
					}

					prop = ss1.str();

				}

				if (count == 2)
				{
					stringstream ss2;
					for (int i = 1; i < tokens.size(); i++)
					{
						ss2 << tokens[i];
						ss2 << " ";
					}

					content = ss2.str();
				}

				if (count == 3)
				{
					Idea idea(prop, content);
					stringstream ss3;

					for (int i = 1; i < tokens.size(); i++)
					{
						ss3 << tokens[i];
						
					}
					vector <string> tokensKey;

					while (getline(ss3, intermediate, ','))
					{
						tokensKey.push_back(intermediate);
					}

					if (tokensKey.size() == 1)
					{
						bool test = false;
						idea.addKeyWord(tokensKey[0]);
					}
					else if(tokensKey.size() > 1)
					{
						for (int i = 0; i < tokensKey.size(); i++)
						{
							idea.addKeyWord(tokensKey[i]);
							bool test = false;
						}
					}

					if (!checkDuplicates(idea))
					{
						ideaObj.push_back(idea);
					}
					
					count = 0;
				}
				
				count++;
			}
	}

}

bool ideaBank::checkDuplicates(Idea Id)
{
	bool test = false;

	for (int i = 0; i < ideaObj.size(); i++)
	{
		if ((Id.prop == ideaObj[i].prop) && (Id.content == ideaObj[i].content) && (Id.kWords.size() == ideaObj[i].kWords.size()))
		{
			for (int k = 0; k < Id.kWords.size(); k++)
			{
				for (int j = 0; j < Id.kWords.size(); j++)
				{
					if (Id.kWords[k] == ideaObj[i].kWords[j])
					{
						test = true;
						break;
					}
							
					if( j == ( Id.kWords.size() -  1) )
					{
						return false;
					}
						
				}

				if (test == true && k == (ideaObj[i].kWords.size()-1))
				{
					return true;
				}
			}
		}
	}

	return test;
}

void ideaBank::binarySearchPrompt()
{
	int number;
	cout << "Enter a number you want to search" << endl;
	cin >> number;
	int value = binarySearch(number);
	if (value != -1)
	{
		cout << "Found at position " << value << endl;
		ideaObj[value].printIdeaContent();
		cout << endl;
	}
	else
	{
		cout << "Not found." << endl;
	}

}

int ideaBank::binarySearch(int target)
{

	Idea id(target);

	int first = 0;
	int last = ideaObj.size() - 1;
	int mid = -1;
	bool found = false;
	while (first <= last)
	{
		mid = (first + last) / 2; // return an integer
		if (id > ideaObj[mid])  // look in upper half
			first = mid + 1;
		else if (id < ideaObj[mid]) // look in lower half
			last = mid - 1;
		else  // target found: force exit
			first = last + 1;
	}

	if (id == ideaObj[mid])
		return mid;
	else
		return -1;
}


#endif 