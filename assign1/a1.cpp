/**** This C++ program uses C++11 functionalities
	Please compile using g++>=4.9 && with the flag -std=c++11
	See 'compile-a1.sh' for readymade compile command
****/


#include <iostream>
#include <string>
#include <regex>

#define FORMAT_ERROR "Please maintain proper format!"

using namespace std;

int process_coordinates(string input, vector<string> *seglist)
{
	std::string::iterator itf = input.begin();
	//string x[3];
	//int flag=2;

	/* check that the string is not empty
		and it starts with a '(' and ends with a ')'*/
	if (input.empty())
		throw "No value given";
	else if (*itf != '(')
		throw FORMAT_ERROR;

	itf = input.end();
	itf--;
	if (*itf != ')')
		throw FORMAT_ERROR;
	/*---------------------------------------*/

	input = input.substr(1, input.length()-2);
	cout<<input<<endl;

	try
	{
		if (regex_match (input, regex("[[:digit:]]+\\,[[:digit:]]+\\,[[:digit:]]+") ))
			// regex comparison expression using ECMAScript syntax
		{
			cout<<"regex match!"<<endl;

			//Split the regex complaint string along ',' character
			stringstream temp(input);
			string segment;
			//vector<string> seglist;
			while(getline(temp, segment, ','))
			{
   				*seglist->push_back(segment);
			}
			int j=0;
			for (vector<string>::const_iterator i = *seglist->begin(); i != *seglist->end(); ++i, j++)
    			cout << *i << ' ';
    		cout<<endl;

    		return 1;
		}
		else
			throw FORMAT_ERROR;
	}
	catch(regex_error& e)
	{
		//extensive regex_error handling
		if (e.code() == regex_constants::error_collate)
			throw "The expression contained an invalid collating element name.";
		//else if (e.code() == regex_constants::codeerror_ctype)
			//throw "The expression contained an invalid character class name.";
		else if (e.code() == regex_constants::error_escape)
			throw "The expression contained an invalid escaped character, or a trailing escape.";
		else if (e.code() == regex_constants::error_backref)
			throw "The expression contained an invalid back reference.";
		else if (e.code() == regex_constants::error_brack)
			throw "The expression contained mismatched brackets ([ and ]).";
		else if (e.code() == regex_constants::error_paren)
			throw "The expression contained mismatched parentheses (( and )).";
		else if (e.code() == regex_constants::error_brace)
			throw "The expression contained mismatched braces ({ and }).";
		else if (e.code() == regex_constants::error_badbrace)
			throw "The expression contained an invalid range between braces ({ and }).";
		else if (e.code() == regex_constants::error_range)
			throw "The expression contained an invalid character range.";
		else if (e.code() == regex_constants::error_space)
			throw "There was insufficient memory to convert the expression into a finite state machine.";
		else if (e.code() == regex_constants::error_badrepeat)
			throw "The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression.";
		else if (e.code() == regex_constants::error_complexity)
			throw "The complexity of an attempted match against a regular expression exceeded a pre-set level.";
		else if (e.code() == regex_constants::error_stack)
			throw "There was insufficient memory to determine whether the regular expression could match the specified character sequence.";
	}
}

int main()
{
	int xs=0, ys=0, zs=0, xe=0, ye=0, ze=0;
	string start, end;
	vector<string> coord_start, coord_end;

	try
	{
		cout<<"Enter the start and end coordinates:"<<endl;
		cout<<"Enter start coordinates in the format (x1,y1,z1): ";
		getline(cin, start);
		cout<<"Enter end coordinates in the format (x2,y2,z2): ";
		getline(cin, end);
		//cout<<start<<endl<<end<<endl;

		process_coordinates(start, &coord_start);
		process_coordinates(end, &coord_end);
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}
	
	return 1;
}