#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
