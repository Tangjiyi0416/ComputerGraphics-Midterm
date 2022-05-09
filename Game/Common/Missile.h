#pragma once
#include "GameObject.h"
#include "Lens.h"
#include "Collider.h"
#include "ICanTakeDamage.h"
#include "Bullet.h"

class Missle :public GameObject
{
public:
	Missle(Faction faction, GLint damage, GameObject* target, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(10.f));
	~Missle();
	void Update(float dt);
	void Draw();
private:
	Faction _faction;
	void Onhit(const Collider& other);
	GameObject* _target;
	GLfloat _track;
	Collider* _collider;
	GLfloat _moveSpeed;
	vec3 _direction;
	GLint _damage;
};