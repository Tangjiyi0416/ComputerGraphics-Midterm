#pragma once
#include "Shape.h"
#define QUAD_NUM 6 

//Quick Step:
//	1.new
//	2.SetShader()
//	3.call Draw;

class Quad :public Shape
{
private:
	Quad(const Quad& q);
public:
	Quad();
	~Quad();
	void Draw();
	void drawW();
	//void Update(float dt);

};
