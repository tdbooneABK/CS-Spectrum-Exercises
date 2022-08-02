#pragma once
#include <map>
#include <string>

class City;

class CityGraph
{
	std::map<std::string, City> m_CitiesMap;
public:
	CityGraph();
	~CityGraph();
	void AddCity(std::string name, float longitude, float latitude);
	void AddTwoWayConnection(std::string city1, std::string city2, float distance);
	void GetPathBetweenCities(std::string city1, std::string city2);
};
