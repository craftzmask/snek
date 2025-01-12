#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, const Color c) const
{
	//gfx.DrawRectDim(x + (loc.x * dimension), y + (loc.y * dimension), dimension, dimension, Colors::Gray);
	const int offsetX = x + borderWidth + padding;
	const int offsetY = y + borderWidth + padding;
	const int x0 = offsetX + (loc.x * dimension) + padding;
	const int y0 = offsetY + (loc.y * dimension) + padding;
	const int x1 = x0 + dimension - padding * 2;
	const int y1 = y0 + dimension - padding * 2;
	gfx.DrawRect(x0, y0, x1, y1, c);
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
	const int screenWidth = 2 * padding + 2 * borderWidth + width * dimension;
	const int screenHeight = 2 * padding + 2 * borderWidth + height * dimension;

	// Draw Top
	gfx.DrawRectDim(x, y, screenWidth, borderWidth, Colors::Blue);

	// Draw Bottom
	gfx.DrawRectDim(x, y + screenHeight - borderWidth, screenWidth, borderWidth, Colors::Blue);

	// Draw Left
	gfx.DrawRectDim(x, y, borderWidth, screenHeight, Colors::Blue);

	// Draw Right
	gfx.DrawRectDim(x + screenWidth - borderWidth, y, borderWidth, screenHeight, Colors::Blue);
}
