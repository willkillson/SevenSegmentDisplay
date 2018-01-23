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

	if (!this->isGameOver) 
	{
		GetInputFromKeybrd();
		UpdatePowerUps();
		UpdateSnake();
		

		if (this->_DidTheSnakeJustEat)
		{
			snekMovePeriod--;
			_DidTheSnakeJustEat = false;
		}

	}

}
void Game::ComposeFrame()
{
	



	if (this->isGameOver == true)
	{
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
	else
	{
		snake.Draw(board);

		auto itb = _powers.begin();
		auto ite = _powers.end();

		for (; itb < ite; itb++)
		{
			itb->Draw(board);
		}

	}





	//////DEBUG 
	SevenSegment counter(700, 150, 1, Colors::Red, gfx);
	SevenSegment xcounter(700, 0, 1, Colors::LightGray, gfx);
	SevenSegment ycounter(700, 50, 1, Colors::LightGray, gfx);
	SevenSegment gameendcode(700, 100, 1, Colors::Red, gfx);
	SevenSegment howmanyeaten(0, 0, 1, Colors::Blue, gfx);


	howmanyeaten.print(_nPowersEaten);
	gameendcode.print(test);
	counter.print(count);
	count++;
	xcounter.print(snake._segments[0].GetLoc().x);
	ycounter.print(snake._segments[0].GetLoc().y);

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
bool Game::isNextAPower()
{
	bool isit = false;
	Location headloc = this->snake.GetNextHeadLocation(this->_delta_loc);


	//////////CREATING NEW POWER UPS

	for (int i = 0; i<	this->_powers.size(); i++)
	{
		if (headloc == this->_powers[i].GetLoc())
		{

			isit = true;
			//swap
			std::swap(_powers[i], _powers[_powers.size() - 1]);
			_powers.pop_back();
		}
	}



	return isit;
}

void Game::GetInputFromKeybrd()
{

	Location current = this->_delta_loc;

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
	else {
		this->_delta_loc = current;
	}
	this->snekMoveCounter++;
}

void Game::UpdatePowerUps()
{
	std::uniform_int_distribution<int> ranx(1, board.GetWidth()-1);
	std::uniform_int_distribution<int> rany(1, board.GetHeight()-1);

	while (this->_powers.size() < 20)
	{
		Location foodloc = { ranx(rng) / board.GetDem(),rany(rng) / board.GetDem() };
		while (!this->snake.isSpotFreeOfSegments(foodloc))
		{
			foodloc = { ranx(rng) / board.GetDem(),rany(rng) / board.GetDem() };
		}
		Power p(foodloc, Colors::Magenta);
		this->_powers.push_back(p);
		if (this->_powers.size() >= 10) {
			break;
		}

	}
}
void Game::UpdateSnake()
{
	if (snekMoveCounter >= snekMovePeriod)
	{
		snekMoveCounter = 0;
		if (!board.isInsideBoard(snake.GetNextHeadLocation(this->_delta_loc)))
		{
			test = 2;//2 means next was out of bounds
			this->isGameOver = true;
		}

		//if the next is a segment, game is over
		if (this->isNextASegment())
		{
			test = 1;//1 means next was a segment
			//this->isGameOver = true;
		}

		else {
			if (this->isNextAPower())
			{
				snake.Grow();
				_nPowersEaten++;
				_DidTheSnakeJustEat = true;
				snake.MoveBy(this->_delta_loc);
			}
			else
			{

				snake.MoveBy(this->_delta_loc);
			}
		}
	}
}

