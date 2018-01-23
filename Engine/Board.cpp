#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	_gfx(gfx)
{


}

void Board::DrawCell(Location & loc, Color c)
{

	assert(loc.x >= 0);
	assert(loc.x < this->_width);
	assert(loc.y >= 0);
	assert(loc.y < this->_height);
	this->_gfx.DrawRectDim(loc.x*this->_dimension, loc.y*this->_dimension, this->_dimension, this->_dimension,  c);
}

bool Board::isInsideBoard(const Location & loc) const
{
	return loc.x>=0 &&loc.x <=_gfx.ScreenWidth&&loc.y>=0&&loc.y<=_gfx.ScreenHeight;
}
