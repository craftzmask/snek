#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	const int offsetX = x + borderPadding + borderThick + cellPadding;
	const int offsetY = y + borderPadding + borderThick + cellPadding;
	const int cellSize = dimension - 2 * cellPadding;
	gfx.DrawRectDim(offsetX + loc.x * dimension, offsetY + loc.y * dimension, cellSize, cellSize, c);
}

void Board::DrawBorders() const
{
	const int top = y;
	const int bottom = y + dimension * height +  2 * (borderThick + borderPadding);
	const int left = x;
	const int right = x + dimension * width + 2 * (borderThick + borderPadding);

	// top
	gfx.DrawRect(left, top, right, top + borderThick, borderColor);

	// right
	gfx.DrawRect(right - borderThick, top, right, bottom, borderColor);

	// bottom
	gfx.DrawRect(left, bottom, right, bottom - borderThick, borderColor);

	// left
	gfx.DrawRect(left, top, left + borderThick, bottom, borderColor);
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
