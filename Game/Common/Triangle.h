#pragma once
#include "Shape.h"
#define TRIANGLE_NUM 3

class Triangle :public Shape
{
private:
	Triangle(const Triangle& q);
	void Init();
public:
	Triangle(vec3& position, vec3& rotation = vec3(), vec3& scale = vec3(1.f));
	Triangle(mat4& localModelMatrix = mat4());
	~Triangle();
	void Draw();
	void drawW();
	//void SetPosition(float dt);

};
