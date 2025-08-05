#pragma once
#include "Level.h"




class Protect_ally_level : public Level {

protected:
	std::vector<allied *> m_allies_to_protect;



public:
	Protect_ally_level(int level_index);
	void update(float dt);
	void init();
	void draw();
	void checkcolitions(float dt);
	
	virtual void check_defeat_condition();
	~Protect_ally_level();

	void remove_all_unactive_objects();

	void update_gameobjects(float dt);

};