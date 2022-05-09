#pragma once
#include "../LinkList.h"
#include "Bullet.h"
#include "Missile.h"
#include "../Header/Angel.h"
class BulletManager
{
private:
	BulletManager();
	~BulletManager();
	static BulletManager* _instance;
	static Linklist<GameObject*> _bullets;
public:
	static BulletManager* GetInstance();
	void SpawnBullet(Faction faction, vec3 direction, vec3 position = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.f), GLint damage = 1);
	void SpawnMissile(Faction faction, GameObject* taget, vec3 position = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.f), GLint damage = 1);
	static void Update(float delta);
	static void Draw();
};