#ifndef Idea_h
#define Idea_h


class Idea
{

public:
	int ID;
	string prop;
	vector< string > kWords;
	string content;
	vector< string > tokcontentVec;
	static int Ident;

	Idea(int id);
	Idea( string propos, string cont ); 
	int getId( int id ) const;
	string getProper( ) const;
	string getContent( ) const;
	vector< string > getKeyWord( ) const;
	void setProper( string p );
	void setContent( string c );
	void addKeyWord( string kw );
	bool checkKeyWordVector( string word ); //task 2
	void printIdeaContent( );
	void addKeyWordToVector( vector< string >& vecWords );
	bool checkKeyContentsIdeaSearch( string word ); //task 2
	void tokenizeContent( );
	bool checkContent( string word );
	void addContentTokenizeToVect( vector< string >& vecWords );
	bool operator >(Idea id) const;
	bool operator <(Idea id) const;
	bool operator ==( Idea id ) const;
};


Idea::Idea(int id)
{
	ID = id;
}

Idea::Idea(string propos, string cont) //4
{
	Ident++;
	ID = Ident;
	prop = propos;
	content = cont;
}

int Idea::getId( int id ) const //1
{
	return ID;
}

string Idea::getProper( ) const //1
{
	return prop;
}

string Idea::getContent( ) const //1
{
	return content;
}

vector< string > Idea::getKeyWord( ) const //1
{
	return kWords;
}

void Idea::setProper( string p ) //1
{
	prop = p;
}

void Idea::setContent( string c ) //1
{
	content = c;
}

void Idea::addKeyWord( string keyword )//1
{ 
	kWords.push_back( keyword );
}


bool Idea::checkKeyWordVector( string word ) //3n+3
{
	if ( kWords.size( ) == 0 )
	{
		return false;
	}
	else
	{
		for ( int i = 0 ; i < kWords.size( ) ; i++ )
		{
			if ( kWords[ i ] == word )
			{
				return true;
			}
		}
	}
	return false;
}

void Idea::printIdeaContent( ) //6n + 13
{
	cout << " Identification Number: " << ID;
	cout << endl;
	cout << " Proposer: " << prop;
	cout << endl;
	cout << " Content: " << content;
	cout << endl;
	cout << " Key Words: ";
	for ( int i = 0 ; i < kWords.size( ) ; i++ )
	{
		if ( i != kWords.size( ) - 1 )
		{
			cout << kWords[ i ] << ", ";
		}
		else
		{
			cout << kWords[ i ];
		}
	}

	cout << endl;
}

//this adds the keywords to the vector 
void Idea::addKeyWordToVector( vector< string >& vecWords ) //3n^2+6n +2
{
	bool test = false;
	for ( int i = 0; i < kWords.size( ); i++ )
	{
		test = false;
		for ( int j = 0 ; j < vecWords.size( ) ; j++ )
		{
			if ( vecWords[ j ] == kWords[ i ] )
			{
				test = true;
			}
		}

		if ( test == false )
		{
			vecWords.push_back( kWords[ i ] );
		}
	}
}

//tokenizes content, then adds it to the vector
void Idea::addContentTokenizeToVect( vector< string >& vecWords ) //4n^2 + 8n + 3
{
	tokenizeContent( ); //n^2 + 2n + 1
	bool test = false;


	for ( int i = 0 ; i < tokcontentVec.size( ) ; i++ )
	{
		test = false;
		for ( int j = 0 ; j < vecWords.size() ; j++ )
		{
			if ( vecWords[ j ] == tokcontentVec[ i ] )
			{
				test = true;
			}
		}

		if ( test == false )
		{
			vecWords.push_back( tokcontentVec[ i ] );
		}
	}

	//vecWords.push_back( content );
}


//check if words are in the contents or if they are in the vector of the keys
bool Idea::checkKeyContentsIdeaSearch( string word ) //4n+6
{
	if ( checkContent( word ) ) //n+4
	{
		return true;
	}

	for ( int i = 0 ; i < kWords.size( ) ; i++ )
	{
		if ( word == kWords[ i ] )
		{
			return true;
		}
	}

	return false;
}

//breaks content into bits
void Idea::tokenizeContent( ) //n^2 + 2n + 1
{
	string intermediate;
	//string s = regex_replace(content, regex(". , ; ^ +| +$|( ) +"), "$1");
	stringstream ss( content );

	char chars[] = ".,;'[]{}\/";
	while (getline(ss, intermediate, ' '))
	{
		for (int i = 0; i < strlen(chars); i++)
		{
			intermediate.erase(remove(intermediate.begin(), intermediate.end(), chars[i]), intermediate.end());
			bool test = true;

			for (int j = 0; j < tokcontentVec.size(); j++)
			{
				if (tokcontentVec[j] == intermediate)
				{
					 test = false;
				}
			}
			
			if (test)
			{
				tokcontentVec.push_back(intermediate);
			}
	
		}
	}
}

//task 2 checks word in content
bool Idea::checkContent( string word ) //n+4
{
	size_t found;
	found = content.find( word ); //n
	if ( found != string::npos )
	{
		return true;
	}

	return false;
}

bool Idea::operator >(Idea ident) const
{
	if (ID > ident.ID)
	{
		return true;
	}
	
	return false;
}

bool Idea::operator <(Idea ident) const
{
	if (ID < ident.ID)
	{
		return true;
	}

	return false;
}

bool Idea::operator ==(Idea id) const
{
	if (ID == id.ID)
	{
		return true;
	}

	return false;
}



int Idea::Ident = 0;
#endif 