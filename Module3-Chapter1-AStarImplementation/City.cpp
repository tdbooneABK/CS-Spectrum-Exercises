#include "City.h"
#include "Link.h"

City::City(std::string name, float lat, float longitude)
	: m_Name(name)
	, m_Lat(lat)
	, m_Long(longitude)
{

}

City::~City()
{
	while (!m_Links.empty())
	{
		delete m_Links.back();
		m_Links.pop_back();
	}
}

void City::AddLink(City* destination, float distance) {
	m_Links.push_back(new Link(this, destination, distance));
}
