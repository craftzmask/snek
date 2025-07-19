#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void Draw(const Location& loc, Color c) const;
	int GetGridWidth() const;
	int GetGridHeight() const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 20;
	static constexpr int height = 20;
	Graphics& gfx;
};