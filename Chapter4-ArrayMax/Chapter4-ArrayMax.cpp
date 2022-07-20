#include <iostream>

using namespace std;

int getMaxElement(int elements[], int size);
void displayArrayValues(int elements[], int size);

int main()
{
    const int kArraySize = 15;
    const int kMaxElementSize = 1000;
    int valuesArray[kArraySize] = {};

    // Create an array kArraySize elements long with random numbers up to kMaxElementSize
    for (int i = 0; i < kArraySize; i++) {
        valuesArray[i] = 1 + (rand() % kMaxElementSize);
    }

    int maxElement = getMaxElement(valuesArray, kArraySize);

    cout << "For array with values: " << endl;
    displayArrayValues(valuesArray, kArraySize);
    cout << "The max value is: " << maxElement;
}


int getMaxElement(int elements[], int size) {
    int maxValue = elements[0];

    for (int i = 1; i < size; i++) {
        if (elements[i] > maxValue) {
            maxValue = elements[i];
        }
    }

    return maxValue;
}

void displayArrayValues(int elements[], int size) {
    for (int i = 0; i < size; i++)
    {
        cout << elements[i] << " ";
    }
    cout << endl;
}
