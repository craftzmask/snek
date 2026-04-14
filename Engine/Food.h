#pragma once
#include "Location.h"
#include "Board.h"

class Food
{
public:
	Food(const Location& loc);
	void Draw(Board& brd) const;
	void Respawn(const Location& loc);
	Location GetLocation() const;
private:
	Location loc;
	Color c = Colors::Red;
};