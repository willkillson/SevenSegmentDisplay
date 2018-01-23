#pragma once
#ifndef POWER_H
#define POWER_H
#include "Colors.h"
#include "Location.h"
#include "Graphics.h"
#include "Board.h"

class Power
{

public:
	Power::Power(Location loc, Color c) { this->_c = c; this->_loc = loc; };
	Location GetLoc() { return this->_loc; }
	void Draw(Board &board)const;

private:

	Location _loc;
	Color _c;

};



#endif