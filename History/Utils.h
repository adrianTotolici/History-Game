#pragma once
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class Utils
{
public:
	Utils();

	void cls(HANDLE hConsole);
	vector<string> makeNewLogSpace(vector<string> vector);
	
	/*Example 
	  _________   _________
	 |         | |         |
	 | screen 1| | screen 2|
	  ---------   ---------     */
	string concat2Screens(vector <string> firstScreen, vector <string> secondScreen);

	/*Example
	 __________    _________
	|          |  |         |
	| screen 1 |  | screen 2|
	|          |  -----------
	|          |  ___________
	|          | | screen 3  |
	------------ -------------    */
	string concat3Screens(vector <string> firsScreen, vector<string> secondScreen, vector<string> thirdScreen);

};

