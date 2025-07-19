#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::Draw(const Location& loc, Color c) const
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, width, height, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}
