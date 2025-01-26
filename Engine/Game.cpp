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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({5, 5}),
	goal(rng, brd, snek)
{
	for (int i = 0; i < brd.nPoisons; i++)
	{
		brd.RespawnPoison(rng, snek, goal);
	}

	for (int i = 0; i < brd.nGoals; i++)
	{
		brd.RespawnGoal(rng, snek);
	}
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

	if (gameStarted && !gameIsOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y != 1)
		{
			delta_loc = { 0, -1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y != -1)
		{
			delta_loc = { 0, 1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x != 1)
		{
			delta_loc = { -1, 0 };
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x != -1)
		{
			delta_loc = { 1, 0 };
		}

		snekMoveCounter += dt;

		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter -= snekMovePeriod;

			const Location next = snek.GetNextHeadLocation(delta_loc);
			
			if (!brd.IsInsideBoard(next) || snek.IsInTileExcepEnd(next) || brd.CheckObstacle(next))
			{
				gameIsOver = true;
			}

			if (!gameIsOver)
			{
				const bool eating = brd.CheckGoal(next);
				if (eating)
				{
					snek.Grow();
					brd.DestroyGoal(next);
				}

				snek.MoveBy(delta_loc);

				if (eating)
				{
					brd.RespawnGoal(rng, snek);
					brd.RespawnObstacle(rng, snek, goal);
				}

				if (brd.CheckPoison(next))
				{
					brd.DestroyPoison(next);
					brd.RespawnPoison(rng, snek, goal);
					snekMovePeriod = std::max(snekMovePeriod - 2.0f * snekSpeedUpFactor, snekMovePeriodMin);
				}
			}
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameStarted = true;
	}
}

void Game::ComposeFrame()
{
	if (gameStarted)
	{
		brd.DrawBorder();
		brd.DrawObstacles(gfx);
		brd.DrawPoisons(gfx);
		brd.DrawGoals(gfx);
		snek.Draw(brd);

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(358, 268, gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(293, 220, gfx);
	}
}
