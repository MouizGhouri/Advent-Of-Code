#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string trimString (string inputString) {
	string outputString = "";
	for (int i = 0; i < inputString.length (); i++) {
		if (!isspace (inputString [i])) {
			outputString = outputString + inputString [i];
		}
	}
	return outputString;
}

vector<string> split (string inputString, char separator = ' ', bool splitByWhiteSpace = false) {
	
	string currentString = "";
	vector<string> extractedStrings;
	
	for (int i = 0; i < inputString.length(); i++) {
		if (splitByWhiteSpace ? isspace(inputString[i]) : inputString[i] == separator) {
			if (currentString.length() != 0) {
				extractedStrings.push_back (currentString);
				currentString = "";
			} else {
				continue;
			}
		} else {
			currentString = currentString + inputString[i];
		}
	}
	
	if (currentString != "") {
		extractedStrings.push_back (currentString);
	}
	
	return extractedStrings;
}

vector<string> getBingoNumbers (string data) {
	string bingoString = "";
	for (int i = 0; i < data.length (); i++) {
		if (!isspace (data [i])) {
			bingoString = bingoString + data [i];
		} else {
			break;
		}
	}
	return split (bingoString, ',');
}

vector<string> getBlock (string data, int blockNumber) {
	
	vector<int> blockData;

	int linesSkipped = 0;
	int linesToSkip = (2 + ((blockNumber) * 5 + ((blockNumber) * 1)));
	
	int startingIndex = -1,
		endingIndex;
	
	string blockString = "";
	
	for (int i = 0; i < data.length (); i++) {
		if (data [i] == '\n') {	
			linesSkipped++;
			if (startingIndex == -1) {
				if (linesSkipped == linesToSkip) {
					startingIndex = i + 1;
					linesSkipped = 0;
				}
			} else {
				if (linesSkipped == 5) {
					endingIndex = i - 1;
					break;
				}
			}
		}
	}
	
	for (int i = startingIndex; i <= endingIndex; i++) {
		blockString = blockString + data [i];
	}
	
	vector<string> blockStringData;
	vector<string> splitData = split (blockString, ' ', true);
	
	for (int i = 0; i < splitData.size (); i++) {
		blockStringData.push_back (trimString (splitData [i]));
	}
	
	return blockStringData;
}

int getNumberOfBlocks (int totalLines) {
	int blocks = 0;
	int blockLines = 0;
	for (int i = 2; i < totalLines; i++) {
		blockLines++;
		if (blockLines == 5) {
			blocks++;
		} else if (blockLines > 5) {
			blockLines = 0;
		}
	}
	return blocks;
}

bool isWinner (string boardData [25]) {
	int checkedCount = 0;
	for (int n = 0; n < 2; n++) {
		for (int i = 0; i < 5; i++) {
			checkedCount = 0;
			for (int j = 0; j < 5; j++) {
				if ((n ? boardData [(i * 5) + j] : boardData [(j * 5) + i]) == "-1") {
					checkedCount++;
				}
			}
			if (checkedCount == 5) {
				return true;
			}
		}
	}
	return false;
}

int getResult (string blockData [25], int bingoNumber) {
	int sumOfUnselected = 0;
	for (int i = 0; i < 25; i++) {
		if (blockData [i] != "-1") {
			sumOfUnselected += stoi (blockData [i]);
		}
	}
	return sumOfUnselected * bingoNumber;
}

int main () {
	
	int totalLines;
	string line, data = "";
	
	ifstream InputFile ("input.txt");
	
	while (getline (InputFile, line)) {
		data = data + line + "\n";
		totalLines++;
	}
	
	InputFile.close();
	
	vector<string> bingoNumbers = getBingoNumbers (data);
	int blocksCount = getNumberOfBlocks (totalLines);
	string blocksData [blocksCount][25];	
	
	for (int i = 0; i < blocksCount; i++) {
		vector<string> blockData = getBlock (data, i);
		for (int j = 0; j < blockData.size(); j++) {
			blocksData [i][j] = blockData [j];
		}
	}

	for (int i = 0; i < bingoNumbers.size (); i++) {
		for (int j = 0; j < blocksCount; j++) {
			for (int k = 0; k < 25; k++) {
				if (blocksData [j][k] == bingoNumbers [i]) {
					blocksData [j][k] = "-1";
				}
			}
			if (isWinner (blocksData [j])) {
				cout << "Sum: " << getResult (blocksData [j], stoi (bingoNumbers [i])) << endl;
				return 1;
			}
		}
	}
	
	return 1;
}
