#pragma once
#include "pch.hpp"
#include "misc.h"
#include "shader.h"
#include "box.h"

class Zombie {
	float cur_rad = 0;
	float rad_to_add = 1;
public:
	Box* body[6];

	Zombie() {
		body[0] = new Box(0, 0.7, 0);
		body[0]->set_size(0.2, 0.2, 0.2);
		body[0]->set_color(0.0f, 1.0f, 1.0f);

		body[1] = new Box(0, 0.4, 0);
		body[1]->set_size(0.2, 0.3, 0.2);
		body[1]->set_color(0.0f, 0.0f, 1.0f);

		body[2] = new Box(0, 0, 0);
		body[2]->set_size(0.08, 0.4, 0.08);
		body[2]->set_color(0.0f, 0.0f, 1.0f);
		
		body[3] = new Box(0.12, 0, 0);
		body[3]->set_size(0.08, 0.4, 0.08);
		body[3]->set_color(0.0f, 0.0f, 1.0f);

		body[4] = new Box(-0.08, 0.35, 0);
		body[4]->set_size(0.08, 0.3, 0.08);
		body[4]->set_color(0.0f, 0.0f, 1.0f);

		body[5] = new Box(0.2, 0.35, 0);
		body[5]->set_size(0.08, 0.3, 0.08);
		body[5]->set_color(0.0f, 0.0f, 1.0f);
		
		
	}

	void draw() {
		update();

		
		
		
		for (auto& p : body) {
			p->draw();
		}
		

	}

	void update() {
		

		body[4]->add_rotate_radian(1, 0, 0);
		body[5]->add_rotate_radian(1, 0, 0);

	}
};