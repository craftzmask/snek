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
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& seg);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snek(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTile(const Location& loc) const;
	bool IsInTileExceptTail(const Location& loc) const;
	Location GetHead() const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};