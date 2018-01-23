#include "Snake.h"
#include <assert.h>



bool Snake::isSpotFreeOfSegments(const Location & loc) const
{

	for (int i = 0; i < this->_nMaxSeg - 1; i++)
	{
		if (this->_segments[i].GetLoc() == loc)
		{
			return false;
		}
	}
	

	return true;
}

Snake::Snake(const Location & loc)
{

	this->_segments[0].InitHead(loc);

	

}
void Snake::MoveBy(const Location & delt_loc)
{


	for (int i = this->_nSeg - 1; i > 0; i--)
	{
		
		this->_segments[i].Follow(this->_segments[i - 1]);
	}

	this->_segments[0].MoveBy(delt_loc);

}
void Snake::Grow()
{
	if (this->_nSeg < this->_nMaxSeg)
	{
		this->_segments[_nSeg].InitBody();
		this->_nSeg++;
	}
}
void Snake::Draw(Board & board) const
{
	for (int i = 0; i < this->_nSeg; i++)
	{
		this->_segments[i].Draw(board);
	}
}

Location Snake::GetNextHeadLocation(const Location & delt_loc) const
{
	Location l(_segments[0].GetLoc());
	l.add(delt_loc);
	return l;
}
	
void Snake::Segment::InitHead(const Location& loc)
{
	this->_loc = loc;
	this->_c = Snake::_headColor;
}
void Snake::Segment::InitBody()
{
	this->_c = Snake::_bodyColor;
}
void Snake::Segment::Follow(const Segment& next)
{
	this->_loc = next._loc;
}
void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	this->_loc.add(delta_loc);
}
void Snake::Segment::Draw(Board& board) const
{
	Location loc = this->_loc;
	board.DrawCell(loc, this->_c);

}

