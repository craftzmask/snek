#pragma once

struct Location
{
	void Add(const Location& loc)
	{
		x += loc.x;
		y += loc.y;
	}
	int x;
	int y;
};