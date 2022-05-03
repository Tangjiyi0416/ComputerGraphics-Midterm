#pragma once
#include "Shape.h"
#define LENS_NUM 50
//resources:
//	Lens basic: https://mathworld.wolfram.com/Circle-CircleIntersection.html
//	solve for x(centered radical line): https://www.wolframalpha.com/input?i2d=true&i=Power%5B%5C%2840%29x-c%5C%2841%29%2C2%5D-Power%5B%5C%2840%29x%2Bd%5C%2841%29%2C2%5D%3DPower%5BR%2C2%5D-Power%5Br%2C2%5D
class Lens :public Shape
{
private:
	Lens(const Lens& q);
	void Init();
	GLfloat _radiusLeft;
	GLfloat _radiusRight;
	GLfloat _offsetLeft;
	GLfloat _offsetRight;
public:
	Lens(vec3& position, vec3& rotation = vec3(), vec3& scale = vec3(1.f));
	Lens(mat4& localModelMatrix = mat4());
	~Lens();
	void Draw();
	void drawW();
	//void SetPosition(float dt);

};
