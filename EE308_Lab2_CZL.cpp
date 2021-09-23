#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

string Keyword[32]=
{
	"auto","break","case","char","const","continue","default","double",
	"do","else","enum","extern","float","for","goto","if","int","long",
	"register","return","short","signed","sizeof","static","struct",
	"switch","typedef","union","unsigned","void","volatile","while"
};

vector<int> Case_num;
int total_num = 0;
int switch_num = 0;
int case_num = 0;
int ifelse_num = 0;
int if_elseif_else_num = 0;
int stack[ 1000 ] = { 0 }; // Build a stack.
int top = -1;

int Correspond( string a , string b )	//	Define a function to correspond with the keyword. YES--->1 NO--->0. 
{
	int correspond( char str );
	int pos = a.find( b , 0 );
	int len = b.length();	
	if( pos != string::npos )
	{
		if( pos == 0 ) 
		{
			if(correspond( a[ pos + len ] ) == 0 )
			{
				return 1;
			}
			else 
			{
				return 0;  
			}  	
		}
		else
		{
			if(correspond( a[ pos + len] ) == 0 && correspond( a[ pos - 1] ) == 0 )
			{
				return 1;
			}
			else
			{
				return 0;
			}	
		}
	}
	return 0;
}

int correspond( char str )	//	If it is the form of letter, YES--->1 NO--->0.  
{
	if( ( str <= 'z' && str >= 'a' ) || ( str <= 'Z' && str >= 'A' ) )
	{
		return 1;
	}
	else
	{
		return 0;	
	}	
}

void sort_1(string str) // Correspond with the keyword, and conclude the number of switch and case.
{
		for(int i = 0; i < 32; i++ )
		{
			if(Correspond( str , Keyword[i] ) == 1)
			{
				if( Correspond( str , "switch" ) )
				{
					Case_num.push_back( case_num );
					switch_num++;
					case_num = 0;
				}
				if( Correspond( str , "case" ))
				{
					case_num++;
				}
				total_num++;
				break;
			}
		}
}

void sort_2( string str )	//	Conclude the number of if_else and if_elseif_else with thw way of nest.
{
	if( Correspond( str , "else if" ) )	//	Correspond else if firstly becacuse it includes if. 
	{
		top++;
		stack[ top ] = 2;
	}	
	else
	{
		if( Correspond( str , "else" ) )
		{
			 if( stack[ top ] == 1 )
			 {
			 	ifelse_num++;
			 	top--;
			 }
			 else
			 {
			 	if( stack[ top ] == 2 )
			 	{
			 		if_elseif_else_num++;
			 		top--;
				 }
			 }
		}
		else
		{
			if( Correspond( str ,"if" ) )
			{
				top++;
				stack[ top ] = 1;
			}
		}
	}
}

int main()
{
	string file,temp;
	cout << "Enter the file path£º" << endl;
	cin >> file;
	ifstream File( file.c_str() );
	int Corrrespond( string a, string b );
	int correspond( char str);
	void sort_1( string str );	//	Correspond with the keyword, and conclude the number of switch and case.
	void sort_2( string str );	//	Conclude the number of if_else and if_elseif_else with thw way of nest.
	while ( getline( File ,temp ))	// Read line by line. 
	{
		istringstream istr ( temp );
		string str;
		sort_2( temp );	//	Blank in the nest of if_else. 
		while( istr >> str ) 
		{
			sort_1( str );
		}
	}
	cout << "total num: " << total_num << endl;
	cout << "switch num: " << switch_num << endl;
	if( !Case_num.empty() )
		{
			Case_num.push_back(case_num);
		}
		else
		{
			Case_num.push_back(0);
		}
		cout << "case_num: ";
		for ( int i = 1; i <= switch_num; i++)
		{
			cout<< Case_num[i] << " ";
		}
		cout << endl;
	cout << "if-else num: " << ifelse_num << endl;
	cout << "if-elseif-else num: " <<if_elseif_else_num << endl;
}
