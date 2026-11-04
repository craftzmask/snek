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
	void DrawFoods() const;

	int GetWidth() const;
	int GetHeight() const;
	bool IsInside(const Location& loc) const;
	bool HasObstacles(const Location& loc) const;
	void UpdateObstacles(std::mt19937& rng, const class Snek& snek);

	void InitPoisons(std::mt19937& rng, const Snek& snek);
	bool HasPoisons(const Location& loc) const;
	void RemovePoison(const Location& loc);

	void InitFoods(std::mt19937& rng, const Snek& snek);
	bool HasFoods(const Location& loc) const;
	void RemoveFood(const Location& loc);
	void SpawnFood(std::mt19937& rng, const Snek& snek);
private:
	static constexpr int x = 20;
	static constexpr int y = 20;
	static constexpr int dimension = 20;
	static constexpr int width = 37;
	static constexpr int height = 27;
	static constexpr int borderThick = 10;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	// Number of poisons should be on the board in term of percent
	static constexpr float poisonCoveragePercent = 0.35;
	static constexpr int nPoisions = int(poisonCoveragePercent * width * height);
	static constexpr int nFoods = 10;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = Colors::Magenta;
	static constexpr Color foodColor = Colors::Red;
	bool hasObstacles[width * height] = { false };
	bool hasPoisons[width * height] = { false };
	bool hasFood[width * height] = { false };
	Graphics& gfx;
};