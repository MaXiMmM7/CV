#pragma once
#include "ofMain.h"
using namespace glm;
class Walker
{
public:

	void setup();
	void setup(vec2 _pos);
	void walk();
	void draw();
	void check_stuck(vector<Walker> _tree);


	vec2 pos;
	bool stuck;
	float point_size = 5;
	

	
};

