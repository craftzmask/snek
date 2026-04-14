#include "Snek.h"

Snek::Snek(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snek::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

void Snek::MoveBy(const Location& deltaLoc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}

	segments[0].MoveBy(deltaLoc);
}

void Snek::GrowUp()
{
	if (nSegments < nSegnmentMax)
	{
		segments[nSegments].InitBody();
		segments[nSegments].Follow(segments[nSegments - 1]);
		++nSegments;
	}
}

Location Snek::GetHead() const
{
	return segments[0].GetLocation();
}

void Snek::Segment::InitHead(const Location& loc)
{
	this->loc = loc;
	c = Snek::headColor;
}

void Snek::Segment::InitBody()
{
	c = Snek::bodyColor;
}

void Snek::Segment::MoveBy(const Location& loc)
{
	this->loc.Add(loc);
}

void Snek::Segment::Follow(const Segment& next)
{
	loc.x = next.loc.x;
	loc.y = next.loc.y;
}

void Snek::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Snek::Segment::GetLocation() const
{
	return loc;
}
