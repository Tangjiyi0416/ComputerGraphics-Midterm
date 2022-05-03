#pragma once
#include "Shape.h"
#define QUAD_NUM 6 

//Quick Step:
//	1.new
//	2.call Draw;

class Quad :public Shape
{
private:
	Quad(const Quad& q);
	void Init();
public:
	Quad(vec3& position, vec3& rotation = vec3(), vec3& scale = vec3(1.f));
	Quad(mat4& localModelMatrix = mat4());
	~Quad();
	void Draw();
	void drawW();
	//void SetPosition(float dt);

};
