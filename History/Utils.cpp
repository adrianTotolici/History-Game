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
	vector.erase(vector.begin()+(vector.size()-2));
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

string Utils::concat3Screens(vector<string> screen1, vector<string> screen2, vector<string> screen3) {
	//remove "/n" return caracter from screen 1
	for (register size_t a = 0; a < screen1.size(); a++) {
		if ((!screen1[a].empty()) && screen1[a].back() == '\n') {
			screen1[a] = screen1[a].substr(0, screen1.size() - 1);
		}
	}

	// add "/n" to second screen
	for (register size_t b = 0; b < screen2.size(); b++) {
		if ((!screen2[b].empty()) && screen2[b].back() != '\n') {
			screen2[b].push_back('\n');
		}

		screen2[b] = "            " + screen2[b];
	}

	// add "/n" to third screen
	for (register size_t c = 0; c < screen3.size(); c++) {
		if ((!screen3[c].empty()) && screen3[c].back() != '\n') {
			screen3[c].push_back('\n');
		}
		screen3[c] = "     " + screen3[c];
	}

	//concat screen 2 and screen 3
	vector<string> screen23;
	for (register size_t d = 0; d < screen2.size(); d++) {
		screen23.push_back(screen2[d]);
	}
	for (register size_t e = 0; e < screen3.size(); e++) {
		screen23.push_back(screen3[e]);
	}

	//add missing lines in screen 1
	size_t screenDiff = 0; 
	if (screen1.size() > screen23.size()) {
		screenDiff = screen1.size() - screen23.size();
		for (register size_t f = 0; f < screenDiff; f++) {
			screen23.push_back("\n");
		}
	}

	//concat screen1 and screen23



	string mainString;
	for (register size_t h = 0; h < screen23.size(); h++) {
		mainString.append(screen1[h]);
		mainString.append(screen23[h]);
	}

	return mainString;
}