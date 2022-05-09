#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Triangle.h"
#include "Quad.h"
#include "SecGun.h"
class Medium :public Enemy
{
public:
	Medium(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Medium();

private:
	void Attack(GLfloat dt);
	void Onhit(const Collider&)override;
	void Move(GLfloat dt)override;
	SecGun* _gun;
	GLfloat _attackTimer = 0;
	int _shots = 0;
	int _destX;
};
