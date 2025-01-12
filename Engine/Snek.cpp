#include "Snek.h"
#include <assert.h>

void Snek::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Snek::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snek::headColor;
}

void Snek::Segment::InitBody()
{
	c = Snek::bodyColor;
}

void Snek::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snek::Segment::MoveBy(const Location& delta_loc)
{
	// either move by 1 horizontally or vertically
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1); 
	loc.Add(delta_loc);
}

const Location& Snek::Segment::GetLocation() const
{
	return loc;
}

Snek::Snek(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snek::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

void Snek::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snek::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody();
		++nSegments;
	}
}

bool Snek::TestCollision(const Location& delta_loc) const
{
	Location next = GetNextHeadLocation(delta_loc);
	for (int i = 1; i < nSegments; ++i)
	{ 
		Location l = segments[i].GetLocation();
		if (next.x == l.x && next.y == l.y)
		{
			return true;
		}
	}
	return false;
}

bool Snek::IsInTile(const Location& target) const
{
	for (int i = 1; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snek::IsInTileExcepEnd(const Location& target) const
{
	for (int i = 1; i < nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

Location Snek::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}
