#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:	Board(Graphics& gfx);
	void DrawCell(const Location loc, Color c);
	bool TestCollision(const Location& first, const Location& second);
	int GetWidth() const;
	int GetHeight() const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 20;
	static constexpr int height = 20;
	Graphics& gfx;
};