#pragma once
#include "GameObject.h"
#include "sgg/graphics.h"


class UI : public GameObject {

	graphics::Brush m_health_brush;	/*Health bar brush*/
	graphics::Brush m_heart_brush;	/*Heart brush*/
	graphics::Brush score;	/*Score and Level brush*/


public:

	UI();
	void update(float dt);
	void init();
	void draw();




};