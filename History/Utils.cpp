#include "stdafx.h"
#include "Utils.h"


Utils::Utils(){}

void Utils::cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
};

vector<string> Utils::makeNewLogSpace(vector<string> vector) {
	for (register size_t i = 1; i<vector.size();i++){
		vector[i - 1] = vector[i];
	}
	vector.erase(vector.begin()+(vector.size()-1));
	return vector;
}

string Utils::concat2Screens(vector<string> screen1, vector<string> screen2) {

	//remove "/n" return caracter from screen 1
	for (register size_t ri = 0; ri < screen1.size(); ri++) {
		if ((!screen1[ri].empty()) && screen1[ri].back() == '\n') {
			screen1[ri] = screen1[ri].substr(0, screen1.size()-1);
		}
	}

	// add "/n" to second screen
	for (register size_t ai = 0; ai < screen2.size(); ai++) {
		if ((!screen2[ai].empty()) && screen2[ai].back() != '\n') {
			screen2[ai].push_back('\n');
		}

		screen2[ai] = "            " + screen2[ai];
	}

	// add missing lines in those two screens
	size_t screenDiffSize = 0;
	if (screen1.size() < screen2.size()) {
		screenDiffSize = screen2.size() - screen1.size();
		for (register size_t si = 0; si < screenDiffSize; si++) {
			screen1.push_back("\n");
		}
	} else {
		screenDiffSize = screen1.size() - screen2.size();
		for (register size_t si = 0; si < screenDiffSize; si++) {
			screen2.push_back("\n");
		}
	}
	
	// concat twho screen in a single screen
	string mainString;
	for (register size_t ci = 0; ci < screen2.size(); ci++) {
		mainString.append(screen1[ci]);
		mainString.append(screen2[ci]);
	}

	return mainString;
}