#pragma once

struct Location
{
	Location Add(const Location& loc)
	{
		x += loc.x;
		y += loc.y;
		return { x, y };
	}

	bool operator == (const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	int x;
	int y;
};