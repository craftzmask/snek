#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Board.h"

class Snek
{
private:
	class Segment
	{
	public:
		void Draw(Board& brd) const;
		void InitHead(const Location& loc);
		void InitBody(const Color bodyColor);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snek(const Location& in_loc);
	void Draw(Board& brd) const;
	void MoveBy(const Location& delta_loc);
	void Grow();
	bool TestCollision(const Location& delta_loc) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileExcepEnd(const Location& target) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;

private:
	static constexpr Color headColor = { 200, 200, 0 }; // dark yellow color
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};