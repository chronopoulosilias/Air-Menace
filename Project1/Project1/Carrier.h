#pragma once
#include "allied.h"



class Carrier : public allied {


	float x_direction = 1.0f;
	bool potision_set = false;


public:
	Carrier();

	void update(float dt);
	void init();
	void draw();






};