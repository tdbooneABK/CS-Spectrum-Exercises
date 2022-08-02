#include "Link.h"

Link::Link(City* source, City* destination, float distance)
	: m_Source(source)
	, m_Destination(destination)
	, m_Distance(distance)
{}

Link::~Link()
{}
