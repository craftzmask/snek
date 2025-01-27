#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Colors.h"
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
	int GetContents(const Location& loc) const;
	void ConsumeContent(const Location& loc);
	void DrawCells() const;
	void RespawnContent(std::mt19937& rng, const class Snek& snek, int contentType);

private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = { 64, 8, 64 };
	static constexpr Color goalColor = Colors::Red;
	static constexpr int cellPadding = 1;
	static constexpr int borderWidth = 5;
	static constexpr int borderPadding = 4;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	int x = 20;
	int y = 20;
	int contents[width * height] = { 0 }; // 0 empty, 1 food, 2 obstacle, 3 poison
	Graphics& gfx;
};