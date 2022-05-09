#pragma once
#include "GameObject.h"
#include "Circle.h"
#include "../LinkList.h"
#include "BossGun.h"
class BossGun;
class BossGunMount :public GameObject
{
public:
	BossGunMount(GLint gunCount = 5, GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~BossGunMount();
	int Shoot();
	void Update(float dt);
	void Draw();
	void AddGun(int number);
	GLint GetGunCount() { return _gunsCount; }
private:
	GLint _gunsCount = 0;
	Linklist<BossGun*> _guns;
	GLfloat _radius;
	GLfloat _rotateSpeed;
};