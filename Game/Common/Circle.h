#pragma once
#include "Shape.h"
#define CIRCLE_NUM 120

class Circle :public Shape
{
private:
	GLfloat _radius;
	Circle(const Circle& q);
	void Init();
public:
	Circle(vec3& position, vec3& rotation = vec3(), vec3& scale = vec3(1.f));
	Circle(mat4& localModelMatrix = mat4());
	~Circle();
	void Draw();
	void drawW();
	//void Update(float dt);

};
