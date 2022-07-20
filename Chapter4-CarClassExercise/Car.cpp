#include "Car.h"
#include <iostream>

using namespace std;

// Contructors
Car::Car()
	: m_year(2022)
	, m_miles(0)
	, m_brand("Unspecified")
{
}

Car::Car(int year, int miles, string brand)
	: m_year(year),
	m_miles(miles),
	m_brand(brand)
{
	m_year = year;
	m_miles = miles;
	m_brand = brand;
}

// Destructor
Car::~Car() {

}

// Member functions
void Car::Display() {
	cout << "Brand: " << m_brand << endl;
	cout << "Year: " << m_year << endl;
	cout << "Miles: " << m_miles << endl;
}

void Car::Drive(int miles) {
	m_miles += miles;
}
