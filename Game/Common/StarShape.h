#pragma once
#include "Shape.h"
#define STAR_NUM 18 

class StarShape :public Shape
{
private:
	StarShape(const StarShape& q);
	void Init();
public:
	StarShape(vec3& position, vec3& rotation = vec3(), vec3& scale = vec3(1.f));
	StarShape(mat4& localModelMatrix = mat4());
	~StarShape();
	void Draw();
	void drawW();
	//void SetPosition(float dt);

};
