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
	snek({ 5, 5 })
{
	brd.Init(rng, snek);
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
			
			float snekModifiedMovePeriod = snekMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				snekModifiedMovePeriod = std::min(snekMovePeriod, snekMovePeriodSpeedup);
			}

			snekMoveCounter += dt;
			if (snekMoveCounter >= snekModifiedMovePeriod)
			{
				snekMoveCounter -= snekModifiedMovePeriod;

				const Location nextHead = snek.GetNextHeadLocation(deltaLoc);
				const Board::ContentType content = brd.GetContent(nextHead);
				if (!brd.IsInside(nextHead) || snek.IsInTileExceptTail(nextHead) || content == Board::ContentType::Obstacle)
				{
					isGameOver = true;
				}

				if (!isGameOver)
				{
					if (content == Board::ContentType::Poison)
					{
						snekMovePeriod = std::max(snekMovePeriod * snekSpeedupFactor, snekMovePeriodMin);
					}

					if (content == Board::ContentType::Food)
					{
						snek.GrowUp();
						snek.MoveBy(deltaLoc);
						brd.SpawnContent(rng, snek, Board::ContentType::Food);
						brd.SpawnContent(rng, snek, Board::ContentType::Obstacle);
					}
					else
					{
						snek.MoveBy(deltaLoc);
					}

					brd.ConsumeContent(nextHead);
				}
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
		brd.DrawCells();
		snek.Draw(brd);;

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
