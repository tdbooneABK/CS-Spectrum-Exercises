#pragma once
#include <string>
#include <vector>

class Link;

class City
{
	float m_Lat;
	float m_Long;
	std::string m_Name;
	std::vector<Link*> m_Links;

public:
	City(std::string name, float lat, float longitude);
	~City();
	void AddLink(City* destination, float distance);
	float GetLat() { return m_Lat; }
	float GetLong() { return m_Long; }
	std::string GetName() { return m_Name; }
	std::vector<Link*> GetLinks() { return m_Links; }
};
