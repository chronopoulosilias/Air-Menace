#pragma once
#include "GameObject.h"
#include "sgg/graphics.h"

class ScreenLevel : public GameObject {
	graphics::Brush m_back_brush; /*Brush background*/
	
	std::vector<std::string>  background_images; /*background images*/

	char info1[40]; /*Text1*/
	char info2[40];	/*Text1*/
	graphics::Brush br; /*text brush*/
	bool pass; /*variable to pass*/

public:
	void update(float dt);
	void init();
	void draw();
	bool passed() { return pass; };
	ScreenLevel(const std::string& name = "START");
	void setMode(std::string	mode);



};