#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, const Color c) const
{
	const int offsetX = x + borderWidth + borderPadding;
	const int offsetY = y + borderWidth + borderPadding;
	const int x0 = offsetX + (loc.x * dimension) + cellPadding;
	const int y0 = offsetY + (loc.y * dimension) + cellPadding;
	gfx.DrawRectDim(x0, y0, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder() const
{
	const int top = y;
	const int bottom = top + 2 * (borderWidth + borderPadding) + height * dimension;
	const int left = x;
	const int right = left + 2 * (borderWidth + borderPadding) + width * dimension;

	// Draw Top
	gfx.DrawRectDim(left, top, right - left, borderWidth, Colors::Blue);

	// Draw Bottom
	gfx.DrawRectDim(x, bottom - borderWidth, right - left, borderWidth, Colors::Blue);

	// Draw Left
	gfx.DrawRectDim(x, y, borderWidth, bottom - top, Colors::Blue);

	// Draw Right
	gfx.DrawRectDim(right - borderWidth, y, borderWidth, bottom - top, Colors::Blue);
}
