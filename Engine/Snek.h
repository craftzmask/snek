#pragma once

#include "Location.h"
#include "Board.h"

class Snek
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody();
		void MoveBy(const Location& loc);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snek(const Location& loc);
	void Draw(Board& brd) const;
	void MoveBy(const Location& deltaLoc);
	void GrowUp();
	bool IsInTile(const Location& loc) const;
	Location GetNextHeadLocation(const Location& deltaLoc) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegnmentMax = 100;
	int nSegments = 1;
	Segment segments[nSegnmentMax];
};