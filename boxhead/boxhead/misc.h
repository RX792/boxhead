#pragma once
#include <iostream>
#include <random>
#include <vector>
using namespace std;

int x_rotate_box = 0;
int y_rotate_box = 0;
int y_revolution = 0;

bool draw_box = true;
bool draw_with_line = false;

random_device rd;
default_random_engine dre{ rd() };
uniform_int_distribution<> uid(0, 1000);

uniform_int_distribution<> uidrad(0, 360);


float windowXY_to_opengl_X(float x) {
	x = (float)(x - (float)800 / 2.0) * (float)(1.0 / (float)(800 / 2.0));
	return x;
}

float windowXY_to_opengl_Y(float y) {
	y = -(float)(y - (float)600 / 2.0) * (float)(1.0 / (float)(600 / 2.0));
	return y;
}