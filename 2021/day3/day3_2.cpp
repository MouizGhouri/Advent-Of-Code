#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

bool strcmp (string str1, string str2, int characters = -1) {
	for (int i = 0; i < (characters == -1 ? str1.length() : characters); i++) {
		if (str1 [i] != str2 [i]) {
			return false;
		}
	}
	return true;
}

char getRateDigit (string data, int totalNumbers, int binaryLength, int index, int rate) {
	
	int onesCount,
		currentIndex;
	
	for (int i = 0; i < totalNumbers; i++) {
		currentIndex = (i * binaryLength) + index;
		if (data [currentIndex] == '1') {
			onesCount++;
		}
	}
	
	switch (rate) {
		case 0 : {
			if ((totalNumbers - onesCount) > onesCount) {
				return '0';
			} else {
				return '1';
			}
			break;
		}
		case 1 : {
			if ((totalNumbers - onesCount) > onesCount) {
				return '1';
			} else {
				return '0';
			}
			break;
		}
	}
}

string getMatchingNumbers (string data, int totalNumbers, int binaryLength, string target) {
	
	int currentIndex;
	string matchedNumbers = "";
	
	for (int i = 0; i < totalNumbers; i++) {
		bool matched = true;
		for (int j = 0; j < target.length(); j++) {
			currentIndex = (i * binaryLength) + j;
			if (data [currentIndex] != target [j]) {
				matched = false;
			}
		}
		if (!matched) {
			continue;
		} else {
			for (int j = 0; j < binaryLength; j++) {
				currentIndex = (i * binaryLength) + j;
				matchedNumbers = matchedNumbers + data [currentIndex];
			}
		}
	}
	
	return matchedNumbers;
	
}

string getRating (string data, int totalNumbers, int binaryLength, int rating) {
	
	string _data = data;
	string ratingString = "";
	
	for (int i = 0; i < binaryLength; i++) {
		ratingString = ratingString + getRateDigit (_data, totalNumbers, binaryLength, i, (rating == 0 ? 0 : 1));
		_data = getMatchingNumbers (_data, totalNumbers, binaryLength, ratingString);
		totalNumbers = _data.length() / binaryLength;
		if (_data.length () == binaryLength) {
			return _data;
		}
	}
	
}

int binaryToDecimal (string binaryNumber) {
	int decimalNumber = 0,
		startingIndex = binaryNumber.length() - 1;
	for (int i = startingIndex; i >= 0; i--) {
		int binaryValue = ((int)binaryNumber[i]) - 48;
		decimalNumber += binaryValue * pow (2, startingIndex - i);
	}
	return decimalNumber;
}

int main () {
	
	string line, 
		   data;
	
	int binaryLength = 0,
		totalNumbers = 0;
	
	ifstream InputFile ("input.txt");
	
	while (getline (InputFile, line)) {
		if (binaryLength == 0) {
			binaryLength = line.length();
		}
		data = data + line;
		totalNumbers++;
	}
	
	InputFile.close();

	
	int rating1 = binaryToDecimal (getRating (data, totalNumbers, binaryLength, 0));
	int rating2 = binaryToDecimal (getRating (data, totalNumbers, binaryLength, 1));
	
	int lifeSupportRating = rating1 * rating2;
	
	cout << lifeSupportRating << endl;
	
	return 1;
}
