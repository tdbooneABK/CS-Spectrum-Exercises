#include <iostream>
#include <string>
#include <thread>


static bool ShouldExit = false;
static int timerValueA = 0;
static int timerValueB = 0;

void Counter(int* value) {
    while (!ShouldExit) {
        *value += 1;
        if (*value > 1000) {
            *value = 0;
        }
    }
}

int main()
{
    std::cout << "Let's start some timers!\n";
    std::thread TimerA(Counter, &timerValueA);
    std::thread TimerB(Counter, &timerValueB);

    char inputChar = ' ';

    while (inputChar != 'q') {
        std::cout << "Enter 'q' to quit; enter any other character to check the timer values." << std::endl;
        std::cin >> inputChar;
        std::cout << "Timer A: " << timerValueA << std::endl;
        std::cout << "Timer B: " << timerValueB << std::endl << std::endl;
    }
    ShouldExit = true;
    
    TimerA.join();
    TimerB.join();

    return 0;
}
