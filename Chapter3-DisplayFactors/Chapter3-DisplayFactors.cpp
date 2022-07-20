#include <iostream>
using namespace std;

int getNumberFromUser();
void printFactorsOfNumber(int number);

int main()
{
    int inputNumber = 0;
    inputNumber = getNumberFromUser();
    printFactorsOfNumber(inputNumber);
}

int getNumberFromUser() {
	cout << "Hello! ";
	while (true)
	{
		int input;
		cout << "Please enter a positive number: ";
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "That is not a number!" << endl;
		}
		else if (input < 1) {
			cout << input << " is not a positive number!" << endl;
		}
		else {
			return input;
		}
	}
}

void printFactorsOfNumber(int number) {
	cout << "Factors of " << number << ":" << endl;
	for (int i = 1; i <= number; i++) {
		if (number % i == 0) {
			cout << i << " ";
		}
	}
}
