#include "Board.h"
#include "Snek.h"
#include "assert.h"

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
	gfx.DrawRectDim(left, top, right - left, borderWidth, borderColor);

	// Draw Bottom
	gfx.DrawRectDim(x, bottom - borderWidth, right - left, borderWidth, borderColor);

	// Draw Left
	gfx.DrawRectDim(x, y, borderWidth, bottom - top, borderColor);

	// Draw Right
	gfx.DrawRectDim(right - borderWidth, y, borderWidth, bottom - top, borderColor);
}

int Board::GetContents(const Location& loc) const
{
	return contents[loc.y * width + loc.x];
}

void Board::ConsumeContent(const Location& loc)
{
	assert(GetContents(loc) == 1 || GetContents(loc) == 3);
	contents[loc.y * width + loc.x] = false;
}

void Board::DrawCells() const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const int content = contents[y * width + x];
			const Location loc = { x, y };

			if (content == 1)
			{
				DrawCell(loc, goalColor);
			}
			else if (content == 2)
			{
				DrawCell(loc, obstacleColor);
			}
			else if (content == 3)
			{
				DrawCell(loc, poisonColor);
			}
		}
	}
}

void Board::RespawnContent(std::mt19937& rng, const Snek& snek, int contentType)
{
	std::uniform_int_distribution<int> xDist(0, GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetHeight() - 1);

	Location newLoc;
	do
	{
		newLoc = { xDist(rng), yDist(rng) };
	} while (snek.IsInTile(newLoc) || contents[newLoc.y * width + newLoc.x] != 0);

	contents[newLoc.y * width + newLoc.x] = contentType;
}

