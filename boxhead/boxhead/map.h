#pragma once
#include "pch.hpp"
#include "box.h"

using namespace std;

class block 
{
public:
	float height;
	int x, y;
	Box* box;

	block(int _x, int _y) 
	{

		x = _x;
		y = _y;
		height = 1;
		box = new Box(x,0,y);
		box->set_size(1, 1, height);
		box->set_random_color();

	}

	void draw() {
		box->draw();
	}
};

class map_manager 
{
public:
	vector<block> blocks;

	int board[10][10] = 
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	map_manager() 
	{

		for (int i = 0; i < 10; i++) 
		{
			for (int j = 0; j < 10; j++) 
			{
				if (board[j][i] == 1)
					blocks.emplace_back(block(j, i));
			}
		}
	}

	void draw() {
		for (auto& p : blocks)
			p.draw();
	}

};