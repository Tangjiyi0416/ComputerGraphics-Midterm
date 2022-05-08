#pragma once
#include "GameObject.h"
#include "Circle.h"
#include "Collider.h"
#include "ICanTakeDamage.h"
enum class Faction
{
	Player, Enemy
};
class Bullet :public GameObject
{
public:
	Bullet(Faction faction, vec3 direction, GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(10.f));
	~Bullet();
	void Update(float dt);
	void Draw();
	//ugly
	void SetDamage(GLint damage);
private:
	Faction _faction;
	void Onhit(const Collider& other);
	Collider* _collider;
	GLfloat _moveSpeed;
	vec3 _direction;
	GLint _damage;
};