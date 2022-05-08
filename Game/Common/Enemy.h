#pragma once
#include "GameObject.h"
#include "../InputUtilities.h"
#include "Collider.h"
#include <functional>
#include "ICanTakeDamage.h"
#include "Player.h"
//Currently I mixed up local and world coordniate in many places, 
// they will work simply because they have no parent, I will fix this in future
//TODO:
//	fix coordniates mixing problem and find a better way to update them
class Enemy :public GameObject, public ICanTakeDamage
{
public:
	virtual ~Enemy();
	virtual void TakeDamage(int damage) override;
	virtual void Update(float dt);
	virtual void Draw();
protected:
	Enemy(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	GLint _health = 10;
	GLfloat _speed = 180.f;
	Collider* _collider;
	GLuint _exp = 1;
	virtual void Onhit(const Collider&);
	virtual void Move(GLfloat dt);
	virtual void Attack(GLfloat dt);
	//Linklist<Bullet*> _bullets;
};