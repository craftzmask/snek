#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim(x + loc.x * dimension, y + loc.y * dimension, dimension, dimension, c);
}

void Board::DrawBorders() const
{
	const int top = y;

	const int left = x;

	const int right = x + dimension * width;

	const int bottom = y + dimension * height;

	const int boardWidth = dimension * width;
	const int boardHeight = dimension * height;

	//// top
	gfx.DrawRect(left - borderThick, top, left + boardWidth + borderThick, top - borderThick, borderColor);

	//// right
	gfx.DrawRect(left + boardWidth, top - borderThick, left + boardWidth + borderThick, top + boardHeight + borderThick, borderColor);


	//// bottom
	gfx.DrawRect(left - borderThick, bottom, left + boardWidth + borderThick, bottom + borderThick, borderColor);

	//// left
	gfx.DrawRect(left, top - borderThick, left - borderThick, top + boardHeight + borderThick, borderColor);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

bool Board::IsInside(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}
