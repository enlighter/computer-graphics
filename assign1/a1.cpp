/**** This C++ program uses C++11 functionalities
	Please compile using g++>=4.9 && with the flag -std=c++11
	See 'compile-a1.sh' for readymade compile command
****/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

#define FORMAT_ERROR "Please maintain proper format!"
#define CUBE_SIZE	1 //cube size of a voxel
#define COORDINATE_SYSTEM	3 //3d coordinate system used here

using namespace std;

/*** 3D coordinates represented as 3 length integer array
with x= a[0], y= a[1] & z= a[2] ***/

static int vertex_count = 1; //to keep track of vertex number for faces

string int_array_to_string(int int_array[], int size_of_array)
{
  string returnstring = "";
  for (int temp = 0; temp < size_of_array; temp++)
    returnstring += to_string(int_array[temp]);
  return returnstring;
}

int process_coordinates(string input, int point[])
{
	std::string::iterator itf = input.begin();
	//int point[3];
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
			vector<string> seglist;
			while(getline(temp, segment, ','))
			{
   				seglist.push_back(segment);
			}
			int j=0;
			for (vector<string>::const_iterator i = seglist.begin(); i != seglist.end(); ++i, j++)
			{
    			cout << *i << ' ';
    			point[j] = std::stoi(*i, NULL, 10); //convert to integer value
			}
    		cout<<endl;

    		for(j=0; j<COORDINATE_SYSTEM; j++)
    			cout<<point[j]<<" ";

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

int draw_point(int point[]) //method to draw a voxel at the point passed
{
	fstream object_file;
	object_file.open("a1.obj", ios :: out | ios :: app);

	if(object_file.fail())
	{
		throw "Couldn't open object file at coordinates: " + int_array_to_string(point, COORDINATE_SYSTEM);
	}
	else
	{
		//vertex 1
		object_file<<"v "<<(float)point[0]-(CUBE_SIZE/(float)2)<<" "<<(float)point[1]-(CUBE_SIZE/(float)2)<<" "<<(float)point[2]+(CUBE_SIZE/(float)2)<<endl;
		//vertex 2
		object_file<<"v "<<(float)point[0]+(CUBE_SIZE/(float)2)<<" "<<(float)point[1]-(CUBE_SIZE/(float)2)<<" "<<(float)point[2]+(CUBE_SIZE/(float)2)<<endl;
		//vertex 3
		object_file<<"v "<<(float)point[0]+(CUBE_SIZE/(float)2)<<" "<<(float)point[1]+(CUBE_SIZE/(float)2)<<" "<<(float)point[2]+(CUBE_SIZE/(float)2)<<endl;
		//vertex 4
		object_file<<"v "<<(float)point[0]-(CUBE_SIZE/(float)2)<<" "<<(float)point[1]+(CUBE_SIZE/(float)2)<<" "<<(float)point[2]+(CUBE_SIZE/(float)2)<<endl;
		//vertex 5
		object_file<<"v "<<(float)point[0]+(CUBE_SIZE/(float)2)<<" "<<(float)point[1]+(CUBE_SIZE/(float)2)<<" "<<(float)point[2]-(CUBE_SIZE/(float)2)<<endl;
		//vertex 6
		object_file<<"v "<<(float)point[0]+(CUBE_SIZE/(float)2)<<" "<<(float)point[1]-(CUBE_SIZE/(float)2)<<" "<<(float)point[2]-(CUBE_SIZE/(float)2)<<endl;
		//vertex 7
		object_file<<"v "<<(float)point[0]-(CUBE_SIZE/(float)2)<<" "<<(float)point[1]-(CUBE_SIZE/(float)2)<<" "<<(float)point[2]-(CUBE_SIZE/(float)2)<<endl;
		//vertex 8
		object_file<<"v "<<(float)point[0]-(CUBE_SIZE/(float)2)<<" "<<(float)point[1]+(CUBE_SIZE/(float)2)<<" "<<(float)point[2]-(CUBE_SIZE/(float)2)<<endl;
		//separator
		object_file<<endl;
		//face 1
		object_file<<"f "<<vertex_count<<" "<<vertex_count+1<<" "<<vertex_count+2<<" "<<vertex_count+3<<endl;
		//face 2
		object_file<<"f "<<vertex_count+4<<" "<<vertex_count+5<<" "<<vertex_count+6<<" "<<vertex_count+7<<endl;
		//face 3
		object_file<<"f "<<vertex_count+1<<" "<<vertex_count+5<<" "<<vertex_count+4<<" "<<vertex_count+2<<endl;
		//face 4
		object_file<<"f "<<vertex_count<<" "<<vertex_count+3<<" "<<vertex_count+7<<" "<<vertex_count+6<<endl;
		//face 5
		object_file<<"f "<<vertex_count<<" "<<vertex_count+6<<" "<<vertex_count+5<<" "<<vertex_count+1<<endl;
		//face 1
		object_file<<"f "<<vertex_count+2<<" "<<vertex_count+4<<" "<<vertex_count+7<<" "<<vertex_count+3<<endl;
		//separator
		object_file<<endl;

		vertex_count += 8;

		cout<<"a voxel written"<<endl;
	}

	return 1;
}

int draw3Dline(int start[], int end[])
//3D DSS line drawing algorithm
{
	int x_gradient = end[0]-start[0], y_gradient = end[1]-start[1], z_gradient = end[2]-start[2];
	int f_xy = 2*y_gradient - x_gradient, f_xz = 2*z_gradient - x_gradient;
	int current_point[COORDINATE_SYSTEM], j=0;

	try
	{
		for(j=0; j<COORDINATE_SYSTEM; j++) //initialize to the start point
			current_point[j] = start[j];

		draw_point(current_point);

		while(current_point[0] < end[0])
		//0th position is the x-coordinate
		//x < xe
		{
			current_point[0]+=1; //x++
			if(f_xy > 0)
			{
				current_point[1]+=1; //y++
				f_xy += 2*(y_gradient - x_gradient);
			}
			else
				f_xy += 2*y_gradient;

			if(f_xz > 0)
			{
				current_point[2]+=1; //z++
				f_xz += 2*(z_gradient - x_gradient);
			}
			else
				f_xy += 2*z_gradient;

			draw_point(current_point);
		}
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		throw "forwarded...";
	}

	return 1;
}

int main()
{
	//int xs=0, ys=0, zs=0, xe=0, ye=0, ze=0;
	string start, end;
	int start_point[COORDINATE_SYSTEM], end_point[COORDINATE_SYSTEM];

	try
	{
		cout<<"Enter the start and end coordinates:"<<endl;
		cout<<"Enter start coordinates in the format (x1,y1,z1): ";
		getline(cin, start);
		cout<<"Enter end coordinates in the format (x2,y2,z2): ";
		getline(cin, end);
		cout<<start<<endl<<end<<endl;

		process_coordinates(start, start_point);
		process_coordinates(end, end_point);

		draw3Dline(start_point, end_point);
	}
	catch(const char* msg)
	{
		cerr<<msg<<endl;
		return 0;
	}
	
	return 1;
}