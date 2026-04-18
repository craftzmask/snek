#include "Snek.h"

Snek::Snek(const Location& loc)
{
	segments[0].InitHead(loc);

	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[] = {
		{10, 100, 32},
		{10, 130, 48},
		{18, 160, 48},
		{10, 130, 48},
	};

	for (int i = 1; i < nSegnmentMax; i++) {
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}
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
		++nSegments;
	}
}

Location Snek::GetNextHeadLocation(const Location& deltaLoc) const
{
	Location loc(segments[0].GetLocation());
	loc.Add(deltaLoc);
	return loc;
}

bool Snek::IsInTile(const Location& loc) const
{
	for (int i = 0; i < nSegments; ++i) {
		const Location segmentLoc = segments[i].GetLocation();
		if (segmentLoc.x == loc.x && segmentLoc.y == loc.y) {
			return true;
		}
	}
	return false;
}

// Prevent the next head touch the tail because next head
// may touch the tail which has not been moved up yet
// causing the wrong detection
bool Snek::IsInTileExceptTail(const Location& loc) const
{
	for (int i = 0; i < nSegments - 1; ++i) {
		const Location segmentLoc = segments[i].GetLocation();
		if (segmentLoc.x == loc.x && segmentLoc.y == loc.y) {
			return true;
		}
	}
	return false;
}

void Snek::Segment::InitHead(const Location& loc)
{
	this->loc = loc;
	c = Snek::headColor;
}

void Snek::Segment::InitBody(Color bodyColor)
{
	c = bodyColor;
}

void Snek::Segment::MoveBy(const Location& loc)
{
	this->loc.Add(loc);
}

void Snek::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snek::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snek::Segment::GetLocation() const
{
	return loc;
}
