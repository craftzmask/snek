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
	snek({5, 5})
{
	for (int i = 0; i < nPoisons; i++)
	{
		brd.RespawnContent(rng, snek, Board::CellContents::Poison);
	}

	for (int i = 0; i < nFoods; i++)
	{
		brd.RespawnContent(rng, snek, Board::CellContents::Food);
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

		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			snekPowerSpeedUpFactor = 2.0f; // double speed when press key space
		}
		else
		{
			snekPowerSpeedUpFactor = 1.0f;
		}

		snekMoveCounter += dt * snekPowerSpeedUpFactor;

		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter -= snekMovePeriod;

			const Location next = snek.GetNextHeadLocation(delta_loc);
			
			if (!brd.IsInsideBoard(next) ||
				snek.IsInTileExcepEnd(next) ||
				brd.GetContents(next) == Board::CellContents::Obstacle)
			{
				gameIsOver = true;
			}

			if (!gameIsOver)
			{
				if (brd.GetContents(next) == Board::CellContents::Food)
				{
					snek.GrowAndMoveBy(delta_loc);
					brd.ConsumeContent(next);
					brd.RespawnContent(rng, snek, Board::CellContents::Food);

					if (nObstacles < maxNObstacles)
					{
						brd.RespawnContent(rng, snek, Board::CellContents::Obstacle);
						nObstacles++;
					}
				}
				else if (brd.GetContents(next) == Board::CellContents::Poison)
				{
					snek.MoveBy(delta_loc);
					brd.ConsumeContent(next);
					brd.RespawnContent(rng, snek, Board::CellContents::Poison);
					snekMovePeriod = std::max(snekMovePeriod - 2.0f * snekSpeedUpFactor, snekMovePeriodMin);
				}
				else
				{
					snek.MoveBy(delta_loc);
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
		brd.DrawCells();
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
