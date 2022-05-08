#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Triangle.h"
#include "MainGun.h"
class Big :public Enemy
{
public:
	Big(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Big();

private:
	void Attack(GLfloat dt);
	void Onhit(const Collider&)override;
	MainGun* _gun;
	GLfloat _attackTimer=0;
	int _shots=0;
};
