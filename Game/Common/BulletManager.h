#pragma once
#include "../LinkList.h"
#include "Bullet.h"
#include "../Header/Angel.h"
class BulletManager
{
private:
	BulletManager();
	~BulletManager();
	static BulletManager* _instance;
	static Linklist<Bullet*> _bullets;
public:
	static BulletManager* GetInstance();
	void SpawnBullet(Faction faction, vec3 direction, vec3 position = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.f));
	static void Update(float delta);
	static void Draw();
};