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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	rng(std::random_device()()),
	snake({0,0})



{

	count = 0;
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

	if (!this->isGameOver) {

	
		if (this->isGoodInput())
		{

	
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			this->_delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			this->_delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			this->_delta_loc = { 1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			this->_delta_loc = { 0,-1 };
		}
		}




		this->snekMoveCounter++;


		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;
			if (!board.isInsideBoard(snake.GetNextHeadLocation(this->_delta_loc)))
			{


				this->isGameOver = true;
			}

			//if the next is a segment, game is over
			if (this->isNextASegment())
			{
				this->isGameOver = true;
			}
			else {

				if (wnd.kbd.KeyIsPressed(VK_CONTROL))
				{
					snake.Grow();
					
				}
				snake.MoveBy(this->_delta_loc);
			}
		}

	}
}
void Game::ComposeFrame()
{

	//counter2.print(wnd.mouse.GetPosY());

	/////
	/////
	//std::uniform_int_distribution<int> colorDist(0, 255);
	//
	//for (int y = 0; y < this->board.GetHeight(); y++)
	//{
	//	for (int x = 0; x < this->board.GetWidth(); x++)
	//	{
	//		Location loc = { x,y };
	//		Color c(colorDist(rng), colorDist(rng), colorDist(rng));
	//		this->board.DrawCell(loc, c);
	//	}
	//}

	

	//Sleep(100);

	//SpriteCodex::DrawTitle(350, 250, gfx);

	if (this->isGameOver == true)
	{
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
	else
	{
		snake.Draw(board);
	}


	int x = 0;
	int y = 0;

	//while(snake.isSpotFreeOfSegments())


	//std::uniform_int_distribution<int> ranx(0, board.GetWidth());
	//std::uniform_int_distribution<int> rany(0, board.GetHeight());
	//
	//while (this->_powers.size() < 10)
	//{
	//	Location foodloc = { ranx(rng),rany(rng) };
	//	while (this->snake.isSpotFreeOfSegments(foodloc))
	//	{
	//		foodloc = { ranx(rng),rany(rng) };
	//		Power p(foodloc, Colors::Red);
	//		this->_powers.push_back(p);
	//	}
	//}

	if (count < 1)
	{
		Location foodloc = { 50,50 };
		Power p(foodloc, Colors::Red);
		this->_powers.push_back(p);
	}
	

		
	//for (int y = 0; y < this->board.GetHeight(); y++)
	//{
	//	for (int x = 0; x < this->board.GetWidth(); x++)
	//	{
	//		//Location loc = { x,y };
	//		Color c(colorDist(rng), colorDist(rng), colorDist(rng));
	//		this->board.DrawCell(loc, c);
	//	}
	//}



	//////
	//////DEBUG SHIT
	SevenSegment counter(5, 0, 1, Colors::Red, gfx);
	SevenSegment counter2(5, 50, 1, Colors::Red, gfx);
	counter.print(count);
	count++;
}



//////////////////



bool Game::isGoodInput()
{
	bool fail_flag = false;

	if (this->_delta_loc.x == -1 && wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		fail_flag = true;
	}
	if (this->_delta_loc.x == 1 && wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		fail_flag = true;
	}
	if (this->_delta_loc.y == 1 && wnd.kbd.KeyIsPressed(VK_UP))
	{
		fail_flag = true;
	}
	if (this->_delta_loc.y == -1 && wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		fail_flag = true;
	}
	return !fail_flag;
}
bool Game::isNextASegment()
{
	bool isit = false;

	Location headloc = this->snake.GetNextHeadLocation(this->_delta_loc);

	//now look through all the segments, and verify its not going to == headloc
	for (int i = 0; i < this->snake.GetnSeg(); i++)
	{
		Location segloc = this->snake._segments[i].GetLoc();
		if (segloc == headloc)
		{
			isit = true;
		}
	}
	return isit;
}
