#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, const Color c) const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder() const;
private:
	int x = 20;
	int y = 20;
	static constexpr int cellPadding = 1;
	static constexpr int borderWidth = 5;
	static constexpr int borderPadding = 4;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr int dimension = 20;
	Graphics& gfx;
};