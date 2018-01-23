#pragma once
#include "Board.h"
#include "Location.h"
#include <vector>


class Snake
{
private:

	class Segment
	{
	public:
		void InitHead(const Location &loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location &delta_loc);
		void Draw(Board &board)const;
		Location GetLoc() const { return this->_loc; }

	private:
		Location _loc;
		Color _c;
	};

public:

	bool isSpotFreeOfSegments(const Location &loc) const;
	Snake(const Location &loc);
	void MoveBy(const Location &delt_loc);
	void Grow();
	void Draw(Board &board)const;
	Location GetNextHeadLocation(const Location &delt_loc)const;
	int GetnSeg() { return this->_nSeg; }
	static constexpr int _nMaxSeg = 500;
	Segment _segments[_nMaxSeg];

private:

	static constexpr Color _headColor = Colors::Yellow;
	static constexpr Color _bodyColor = Colors::Green;


	int _nSeg = 1;


	
};

