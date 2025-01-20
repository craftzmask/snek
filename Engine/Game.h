/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snek.h"
#include "Goal.h"
#include "Rock.h"
#include "FrameTimer.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int nRocksMax = 20;
	static constexpr float rockSpawnPeriod = 5.0f; // spawn a rock every 20 seconds
	float rockCounterPeriod = 0.0f;
	int nRocks = 0;
	FrameTimer ft;
	std::mt19937 rng;
	Board brd;
	Snek snek;
	Goal goal;
	Rock rocks[nRocksMax];
	Location delta_loc = { 1, 0 };
	static constexpr float snekMovePeriodMin = 0.1f;		// snek moves by 1 location in minimum 0.1 seconds
	static constexpr float snekSpeedUpFactor = 0.001f;		// reduce time move by this amount
	float snekMovePeriod = 0.3f;							// snek moves by 1 location in X seconds
	float snekMoveCounter = 0.0f;							// keep track the current time passed to move snek
	static constexpr float goalExistedPeriod = 10.0f;
	float goalPeriodCounter = 0.0f;
	bool gameStarted = false;
	bool gameIsOver = false;
	/********************************/
};