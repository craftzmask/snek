#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	const int x0 = x + padding + loc.x * dimension;
	const int x1 = x0 + dimension - 2 * padding;

	const int y0 = y + padding + loc.y * dimension;
	const int y1 = y0 + dimension - 2 * padding;

	gfx.DrawRect(x0, y0, x1, y1, c);
}

void Board::DrawBorders() const
{
	const int top = y;
	const int left = x;
	const int right = x + dimension * width;
	const int bottom = y + dimension * height;

	const int boardWidth = dimension * width;
	const int boardHeight = dimension * height;

	// top
	gfx.DrawRect(left - borderThick, top, left + boardWidth + borderThick, top - borderThick, borderColor);

	// right
	gfx.DrawRect(left + boardWidth, top - borderThick, left + boardWidth + borderThick, top + boardHeight + borderThick, borderColor);

	// bottom
	gfx.DrawRect(left - borderThick, bottom, left + boardWidth + borderThick, bottom + borderThick, borderColor);

	// left
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
