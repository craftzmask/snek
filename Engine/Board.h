#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	enum class ContentType
	{
		Empty,
		Food,
		Obstacle,
		Poison
	};

public:	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c) const;
	void DrawCells() const;
	void DrawBorders() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInside(const Location& loc) const;
	void Init(std::mt19937& rng, const class Snek& snek);
	ContentType GetContent(const Location& loc) const;
	void ConsumeContent(const Location& loc);
	void SpawnContent(std::mt19937& rng, const class Snek& snek, ContentType contentType);
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
	static constexpr Color poisonColor = Color(57, 0, 55);
	static constexpr Color foodColor = Colors::Red;
	ContentType contents[width * height] = { ContentType::Empty };
	Graphics& gfx;
};