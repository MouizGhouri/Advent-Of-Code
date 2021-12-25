#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

string getRate (int rateType, string data, int binaryLength, int numberOfLines) {
	
	string rate;
	
	int index;
	int oneCounts [binaryLength] = { 0 }; 
	
	for (int i = 0; i < numberOfLines; i++) {
		index = i * binaryLength;
		for (int j = 0; j < binaryLength; j++) {
			if (data [index + j] == '1') {
				oneCounts [j]++;
			}
		}
	}

	for (int i = 0; i < binaryLength; i++) {
		int zeroCounts = (numberOfLines - oneCounts [i]); 
		if (rateType == 0) {	
			if (zeroCounts > oneCounts [i]) {
				rate = rate + "0";
			} else {
				rate = rate + "1";
			}
		} else {
			if (zeroCounts < oneCounts [i]) {
				rate = rate + "0";
			} else {
				rate = rate + "1";
			}
		}
	}
	
	return rate;
}

int binaryToDecimal (string binaryString) {
	int decimal = 0,
		length = (binaryString.length() - 1);
	for (int i = length; i >= 0; i--) {
		int binaryValue = ((int)binaryString [i]) - 48;
		decimal += binaryValue * (pow (2, length - i));
	}
	return decimal;
}

int main () {
	
	string line = "", 
		   data = "";
		   
	int binaryLength = 0,
		numberOfLines = 0;
	
	ifstream InputFile ("input.txt");
	
	while (getline (InputFile, line)) {
		if (binaryLength == 0) {
			while (line [binaryLength]) {
				binaryLength++;
			}
		}
		data = data + line;
		numberOfLines++;
	}
	
	InputFile.close ();
	
	int gammaRateValue = binaryToDecimal (getRate (0, data, binaryLength, numberOfLines));
	int epsilonRateValue = binaryToDecimal (getRate (1, data, binaryLength, numberOfLines));
	
	cout << gammaRateValue << endl;
	cout << epsilonRateValue << endl;
	
	int resultValue = gammaRateValue * epsilonRateValue;

	cout << "Answer : " << resultValue;
	
	return 1;
}
