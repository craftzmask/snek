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

	bool CheckObstacle(const Location& loc) const;
	void DrawObstacles(Graphics& gfx) const;
	void RespawnObstacle(std::mt19937& rng, const class Snek& snek);

	bool CheckPoison(const Location& loc) const;
	void DestroyPoison(const Location& loc);
	void DrawPoisons(Graphics& gfx) const;
	void RespawnPoison(std::mt19937& rng, const class Snek& snek);

	bool CheckGoal(const Location& loc) const;
	void DestroyGoal(const Location& loc);
	void DrawGoals(Graphics& gfx) const;
	void RespawnGoal(std::mt19937& rng, const class Snek& snek);

private:
	void DrawCells(const bool field[], Color color) const;

private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = Colors::Magenta;
	static constexpr Color goalColor = Colors::Red;
	static constexpr int cellPadding = 1;
	static constexpr int borderWidth = 5;
	static constexpr int borderPadding = 4;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;

	int x = 20;
	int y = 20;
	bool hasObstacles[width * height] = { false };
	bool hasPoisons[width * height] = { false };
	bool hasGoals[width * height] = { false };
	Graphics& gfx;

public:
	static constexpr int nPoisons = (width * height) / 3;
	static constexpr int nGoals = 10;
};