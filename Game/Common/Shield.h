#pragma once
#include "GameObject.h"
#include "Circle.h"
#include "../LinkList.h"
class Shield :public GameObject
{
public:
	Shield(GLint shieldCount = 5, GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Shield();
	void Update(float dt);
	void Draw();
	void AddShield(int number);
	GLint GetShieldCount() { return _shieldCount; }
private:
	Linklist<Shape*> _shieldShapes;
	GLint _shieldCount=0;
	GLfloat _radius;
	GLfloat _rotateSpeed;
	mat4 _shieldScaleMatrix;
};