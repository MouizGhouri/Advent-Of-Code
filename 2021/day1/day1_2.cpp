#include <iostream>
#include <fstream>

using namespace std;

int getSum (int array [], int length)  {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += array [i];
	} 
	return sum;
}

void addNumberToIntArray (int array [], int length, int number) {
	for (int i = length; i >= 0; i--) {
		if (i == 0) {
			array [i] = number;
		} else {
			array [i] = array [i - 1];
		}
	}
}

int main () {
	
	int numbers [3] = { 0, 0, 0 };
	
	int lines = 0,
		oldSum = 0,
		increased = 0;
		
	string line;
	
	ifstream InputFile ("input.txt");
	
	while (getline (InputFile, line)) {
		
		addNumberToIntArray (numbers, sizeof (numbers) / sizeof (numbers [0]), stoi(line));
		lines++;
		
		if (lines >= 3) {
			int newSum = getSum (numbers, sizeof (numbers) / sizeof (numbers [0]));
			if (newSum > oldSum && oldSum != 0) {
				increased++;
			}
			oldSum = newSum;
		}
		
	}
	
	InputFile.close ();
	
	cout << increased << endl;
	
	return 1;
}
