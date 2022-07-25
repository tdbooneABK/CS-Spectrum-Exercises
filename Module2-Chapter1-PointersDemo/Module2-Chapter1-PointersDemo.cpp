#include <iostream>

int main()
{
    int a;
    int b;
    int* ptra = &a;
    int* ptrb = &b;

    std::cout << "What should be the value of a? ";
    std::cin >> a;
    std::cout << "What should be the value of b? ";
    std::cin >> b;
    std::cout << "a: " << *ptra << " b: " << *ptrb << std::endl;
}
