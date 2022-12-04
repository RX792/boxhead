#pragma once
#include "pch.hpp"
#include "Entity.hpp"
#include "GameScene.hpp"
#include "Scene.hpp"

using namespace std;

class block 
{
public:
	float height;
	int x, y;

	block(int _x, int _y) 
	{

		x = _x;
		y = _y;
		height = 1;
		

	}

	void draw() {

	}
};

class Map_manager : public Entity
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

	

	Map_manager() :  Entity()
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

	virtual ~Map_manager()
	{}

	void create_box(Scene* s) {

		for (auto& p : blocks) {
			auto a = s->Scene::CreateEntity<Entity>();
			a->MoveTo(p.x, 0.0f, p.y);
		}
		


	}

};