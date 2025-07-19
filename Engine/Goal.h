#pragma once
#include "Board.h"
#include "Snek.h"

class Goal
{
public:
	Goal(const Location& loc, Color c);
	void Draw(Board& brd) const;
	void Respawn(const Board& brd, const Snek& snek);
	bool TestCollision(const Location& other) const;
private:
	Location loc;
	Color c;
};