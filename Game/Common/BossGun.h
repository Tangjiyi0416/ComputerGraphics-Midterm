#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "Circle.h"
#include "../InputUtilities.h"
#include "../LinkList.h"
#include "BulletManager.h"
#include "Player.h"

//temp implement
class BossGun :public GameObject
{
public:
	BossGun( GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(.5f));
	~BossGun();
	bool Shoot();
	void Update(float dt);
	void Draw();
private:
	GLfloat _cooldown = .2f;
	GLfloat _curCooldown = 0.f;
	Faction _faction;
};