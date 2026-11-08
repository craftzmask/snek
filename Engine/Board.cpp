#include "Board.h"
#include "Snek.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c) const
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

int Board::GetContent(const Location& loc) const
{
	return contents[loc.y * width + loc.x];
}

void Board::ConsumeContent(const Location& loc)
{
	contents[loc.y * width + loc.x] = 0;
}

void Board::SpawnContent(std::mt19937& rng, const Snek& snek, int contentType)
{
	std::uniform_int_distribution<int> xDist(0, GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || GetContent(newLoc) != 0);

	contents[newLoc.y * width + newLoc.x] = contentType;
}

void Board::DrawCells() const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const Location loc = { x, y };
			const int content = contents[y * width + x];
			if (content == 1)
			{
				DrawCell(loc, obstacleColor);
			}
			else if (content == 2)
			{
				DrawCell(loc, foodColor);
			}
			else if (content == 3)
			{
				DrawCell(loc, poisonColor);
			}
		}
	}
}

void Board::Init(std::mt19937& rng, const Snek& snek)
{
	for (int i = 0; i < nPoisions; i++)
	{
		SpawnContent(rng, snek, 3);
	}
	for (int i = 0; i < nFoods; i++)
	{
		SpawnContent(rng, snek, 2);
	}
}

