#pragma once
#include "Shape.h"
#define LENS_NUM 5

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
	//void Update(float dt);

};
