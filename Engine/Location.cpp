#include "Location.h"

bool Location::operator==(const Location & rhs)
{
	return	this->x == rhs.x&&this->y == rhs.y;
}
