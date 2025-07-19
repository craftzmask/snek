#include "Snek.h"
#include "Goal.h"

Snek::Snek(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snek::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = headColor;
}

void Snek::Segment::InitBody()
{
	c = bodyColor;
}

void Snek::Segment::MoveBy(const Location& delta_loc)
{
	loc.Add(delta_loc);
}

void Snek::Segment::Follow(const Segment& seg)
{
	loc = seg.loc;
}

void Snek::Segment::Draw(Board& brd) const
{
	brd.Draw(loc, c);
}

Location Snek::Segment::GetLocation() const
{
	return loc;
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

void Snek::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snek::IsInTile(const Location& loc) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].IsInTile(loc))
		{
			return true;
		}
	}
	return false;
}

Location Snek::GetHead() const
{
	return segments[0].GetLocation();
}

Location Snek::GetNextLocation(const Location& delta_loc) const
{
	Location next = { GetHead().x + delta_loc.x, GetHead().y + delta_loc.y };
	return next;
}


bool Snek::Segment::IsInTile(const Location& other) const
{
	return loc.x == other.x && loc.y == other.y;
}
