#pragma once
#include "GameObject.h"
#include "StarShape.h"
#include <ctime>
#include <iostream>
class Star :public GameObject
{
public:
	Star(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Star();
	void Update(float dt);
	void Draw();
private:

	GLfloat _speed;
	GLfloat _counter;
	GLfloat Bezier(GLfloat t);
};
