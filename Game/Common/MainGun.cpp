#include "MainGun.h"

MainGun::MainGun(Faction faction, GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ faction }, GameObject{
	parent, localPosition, localRotation, localScale
}
{
	_shapesNumber = 2;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Circle;
	_shapes[1] = new Quad;
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}

	_direction = faction == Faction::Player ? vec3(0, 1, 0) : vec3(0, -1, 0);
}

MainGun::~MainGun()
{
}
bool MainGun::Shoot()
{
	if (_curCooldown <= 0) {
		//std::cout << "gun faction:" << (int)_faction << std::endl;

		BulletManager::GetInstance()->SpawnBullet(_faction, _direction, ToWorld(localPosition), _faction == Faction::Player ? Player::GetInstance()->damage : 1);
		_curCooldown = _cooldown;
		return true;
	}
	return false;
}
void MainGun::Update(float dt) {
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_curCooldown -= dt;
}

void MainGun::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
}