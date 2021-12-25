#include <iostream>
#include <fstream>

using namespace std;

int main () {

	string line;
		
	ifstream InputFile ("input.txt");
	
	int oldNumber = -1,
		increases = 0;
	
	while (getline (InputFile, line)) {
		int number = stoi(line);
		if (oldNumber != -1) {
			if (number > oldNumber) {
				cout << "Increased\n";
				increases += 1;
			} else {
				cout << "Nothing\n";
			}
		} 	
		oldNumber = number;
	}
	
	cout << "\n";
	cout << increases << endl;
	
	InputFile.close ();
	
	cout << "Done!";

	return 1;
}
