#pragma once
#include "allied.h"



class ally_fighter : public allied {


	bool left;




public :
	ally_fighter(bool left);
	void update(float dt);
	void draw();
	void init();

};