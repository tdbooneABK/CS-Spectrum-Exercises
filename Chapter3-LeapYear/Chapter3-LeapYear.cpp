#include <iostream>
using namespace std;

bool isYearALeapYear(int year);

int main()
{
    int inputYear = 0;

    cout << "What year is it right now?" << endl;
    cin >> inputYear;
    cout << "It is " << (isYearALeapYear(inputYear) ? "" : "not ") << "a leap year." << endl;

}

bool isYearALeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            }
            else
            {
                return false;
            }
        }
        else {
            return true;
        }
    }
    else
    {
        return false;
    }
}