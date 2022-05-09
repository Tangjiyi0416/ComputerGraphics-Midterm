#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Triangle.h"
#include "BossGunMount.h"
#include "BulletManager.h"
class Boss0 :public Enemy
{
public:
	~Boss0();
	static Boss0* GetInstance() {
		if (_instance == nullptr)
			_instance = new Boss0(nullptr, vec3(0, SCREEN_HEIGHT, 0), vec3(), vec3(12.f));
		return _instance;
	}
private:
	Boss0(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	static Boss0* _instance;
	void Move(GLfloat dt)override;
	void Onhit(const Collider&)override;
	void Attack(GLfloat dt);

	GLfloat _moveTimer = 0;
	void OnKilled()override;
	vec3 _direction;
	BossGunMount* _gun;
	GLfloat _attackTimer = 0;
	int _shots = 0;
	//ugly
	bool _wp1 = false;
	bool _wp2 = true;
	vec3 _dests[4];
	int _dest=0;
};
