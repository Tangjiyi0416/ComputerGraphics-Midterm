#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Lens.h"
#include "RotateGun.h"
class Sentinel :public Enemy
{
public:
	Sentinel(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Sentinel();

private:
	void Attack(GLfloat dt);
	void Move(GLfloat dt)override;
	void Onhit(const Collider&)override;
	vec3 _destination;
	RotateGun* _gun;
	GLfloat _attackTimer = 0;
	int _shots = 0;
};
