#include <iostream>
#include <fstream>

using namespace std;

int getMagnitude (string commandLine) {
	string magnitude;
	int index = commandLine.length() - 1;
	while (!isspace (commandLine [index])) {
		magnitude = magnitude + commandLine [index];
		index--;
	}
	return stoi(magnitude);
}

void executeCommand (int positionArray[2], string commandLine) {
	
	cout << positionArray [0] << " " << positionArray [1] << endl;
	
	int magnitude = getMagnitude (commandLine);
	
	switch (commandLine [0]) {
		case 'f': {
			positionArray [0] += magnitude;
			positionArray [1] += (magnitude * positionArray[2]);
			break;
		}
		case 'd' : {
			positionArray [2] += magnitude;
			break;
		}
		case 'u' : {
			positionArray [2] -= magnitude;
			break;
		}
	}
	
}

int main () {
	
	string line;
	
	int position [3] = { 0, 0, 0 };
	
	ifstream InputFile ("input.txt");
	
	while (getline (InputFile, line)) {
		executeCommand (position, line);
	}
	
	InputFile.close ();
	
	cout << position [0] << " x " << position [1] << " = " << position [0] * position [1] << endl;
	cout << "Done!" << endl;
	
	return 1;
}
