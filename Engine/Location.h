#pragma once

struct Location
{
	Location Add(const Location& loc)
	{
		x += loc.x;
		y += loc.y;
		return { x, y };
	}

	int x;
	int y;
};