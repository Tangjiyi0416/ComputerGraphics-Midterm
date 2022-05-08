#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Triangle.h"
#include "MainGun.h"
#include "Boss2.h"
class Boss1 :public Enemy
{
public:
	Boss1(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Boss1();

private:
	void Move(GLfloat dt)override;
	void Onhit(const Collider&)override;
	GLfloat _moveTimer = 0;
};
