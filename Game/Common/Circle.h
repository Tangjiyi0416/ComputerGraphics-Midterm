#pragma once
#include "Shape.h"
#define CIRCLE_NUM 120
//Quick Step:
//	1.new
//	2.SetShader()
//	3.call Draw;

class Circle :public Shape
{
private:
	GLfloat _radius;
	Circle(const Circle& q);
public:
	Circle(GLfloat radius = 1.f);
	~Circle();
	void Draw();
	void drawW();
	//void Update(float dt);

};
