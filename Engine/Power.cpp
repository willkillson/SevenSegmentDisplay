#include "Power.h"

void Power::Draw(Board & board)const
{
	Location l = this->_loc;
	board.DrawCell(l, this->_c);

}
