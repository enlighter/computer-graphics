#include <iostream>
#include <string>
#include <regex>

#define FORMAT_ERROR "Please maintain proper format!"

using namespace std;

int process_coordinates(string input)
{
	std::string::iterator itf = input.begin();
	string x[3];
	int flag=2;

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

	if (std::regex_match (input, std::regex("(([0-9])\\w*),(([0-9])\\w*),(([0-9])\\w*)") ))
	{

	}
	else
		throw FORMAT_ERROR;

	/*for (itf = input.begin(); itf != input.end(); ++itf)
	{
		if (*itf == ',')
		{
			
		}
	}*/
}

int main()
{
	int xs=0, ys=0, zs=0, xe=0, ye=0, ze=0;
	string start, end;

	try
	{
		cout<<"Enter the start and end coordinates:"<<endl;
		cout<<"Enter start coordinates in the format (x1,y1,z1): ";
		getline(cin, start);
		cout<<"Enter end coordinates in the format (x2,y2,z2): ";
		getline(cin, end);
		cout<<start<<endl<<end<<endl;

		process_coordinates(start);
		process_coordinates(end);
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}
	
	return 1;
}