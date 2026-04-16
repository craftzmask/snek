#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorders() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInside(const Location& loc) const;
private:
	int x = 50;
	int y = 50;
	static constexpr int dimension = 20;
	static constexpr int width = 35;
	static constexpr int height = 25;
	static constexpr int borderThick = 10;
	static constexpr int padding = 5;
	static constexpr Color borderColor = Colors::Blue;
	Graphics& gfx;
};