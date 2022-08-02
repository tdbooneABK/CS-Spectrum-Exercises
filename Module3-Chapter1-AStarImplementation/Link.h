#pragma once

class City;

class Link
{
	City* m_Source;
	City* m_Destination;
	float m_Distance;
public:
	Link(City* source, City* destination, float distance);
	~Link();
	City* GetSource() { return m_Source; }
	City* GetDestination() { return m_Destination; }
	float GetDistance() { return m_Distance; }
};
