#pragma once
#include "Shape.h"

//Quick Step:
//	1.new
//	2.SetShader()
//	3.call Draw;

class Triangle :public Shape
{
private:
	Triangle(const Triangle& q);
public:
	Triangle();
	~Triangle();
	void Draw();
	void drawW();
	//void Update(float dt);

};
