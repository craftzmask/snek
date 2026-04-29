/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <cmath>
#include <algorithm>
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(rd()),
	brd(gfx),
	snek({ 5, 5 }),
	food(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if (isGameStarted)
	{
		if (!isGameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP) && deltaLoc.y != 1)
			{
				deltaLoc = { 0, -1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN) && deltaLoc.y != -1)
			{
				deltaLoc = { 0, 1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT) && deltaLoc.x != 1)
			{
				deltaLoc = { -1, 0 };
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT) && deltaLoc.x != -1)
			{
				deltaLoc = { 1, 0 };
			}

			snekMoveCounter += dt;
			if (snekMoveCounter >= snekMovePeriod)
			{
				const Location nextHead = snek.GetNextHeadLocation(deltaLoc);
				if (!brd.IsInside(nextHead) || snek.IsInTileExceptTail(nextHead) || brd.HasObstacles(nextHead))
				{
					isGameOver = true;
				}

				if (!isGameOver)
				{
					if (nextHead == food.GetLocation())
					{
						snek.GrowUp();
						snek.MoveBy(deltaLoc);
						food.Respawn(rng, brd, snek);
						brd.UpdateObstacles(rng, snek, food);
					}
					else
					{
						snek.MoveBy(deltaLoc);
					}
				}

				snekMoveCounter = 0.0f;
			}
			
			snekSpeedUpCounter += dt;
			if (snekSpeedUpCounter >= snekSpeedUpPeriod)
			{
				snekSpeedUpCounter = snekSpeedUpPeriod - snekSpeedUpCounter;
				snekMovePeriod = std::max(snekMovePeriod - 0.01f, minSnekSpeedUpPeriod);
			}
		}
	}
	else
	{
		isGameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
	
}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		brd.DrawBorders();
		brd.DrawObstacles();

		snek.Draw(brd);
		food.Draw(brd);

		if (isGameOver)
		{
			SpriteCodex::DrawGameOver(358, 268, gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(293, 220, gfx);
	}
}
