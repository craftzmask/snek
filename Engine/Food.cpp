#include "Food.h"

Food::Food(const Location& loc)
{
	this->loc = loc;
}

void Food::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Food::Respawn(const Location& loc)
{
	this->loc = loc;
}

Location Food::GetLocation() const
{
	return loc;
}
