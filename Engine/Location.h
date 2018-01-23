#pragma once
#ifndef LOCATION_H
#define LOCATION_H

class Location {

public:
	void add(const Location &val)
	{
		x += val.x;
		y += val.y;
	}
	bool operator == (const Location &rhs);

	int x;
	int y;
};

#endif