#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c) const;
	void DrawBorders() const;
	void DrawObstacles() const;
	void DrawPoisons() const;

	int GetWidth() const;
	int GetHeight() const;
	bool IsInside(const Location& loc) const;
	bool HasObstacles(const Location& loc) const;
	void UpdateObstacles(std::mt19937& rng, const class Snek& snek, const class Food& goal);

	void InitPoisons(std::mt19937& rng, const Snek& snek, const Food& food);
	bool HasPoisons(const Location& loc) const;
private:
	static constexpr int x = 20;
	static constexpr int y = 20;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr int borderThick = 10;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	static constexpr int nPoisions = int(0.35 * width * height);
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = Colors::Magenta;
	bool hasObstacles[width * height] = { false };
	bool hasPoisons[width * height] = { false };
	Graphics& gfx;
};