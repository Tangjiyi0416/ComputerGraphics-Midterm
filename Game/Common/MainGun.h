#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "Circle.h"
#include "../InputUtilities.h"
#include "../LinkList.h"
#include "BulletManager.h"
#include "Player.h"
class MainGun :public GameObject
{
public:
	MainGun(Faction faction, GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(.5f));
	~MainGun();
	bool Shoot();
	void Update(float dt);
	void Draw();
private:
	GLfloat _cooldown = .1f;
	GLfloat _curCooldown = 0.f;
	Faction _faction;
	vec3 _direction;
};