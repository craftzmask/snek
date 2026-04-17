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
	static constexpr int x = 20;
	static constexpr int y = 20;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr int borderThick = 10;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	static constexpr Color borderColor = Colors::Blue;
	Graphics& gfx;
};