#include "MainGun.h"

MainGun::MainGun(Faction faction, GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ faction }, GameObject{
	parent, localPosition, localRotation, localScale
}
{
	_shapesNumber = 2;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Circle(vec3(), vec3(), vec3(1.2f, 1.2f, 0));
	_shapes[1] = new Quad;
	_shapes[0]->SetColor(vec4(0.1f, 0.3f, .3f, 1));
	_shapes[1]->SetColor(vec4(0.6f, 0.6f, .6f, 1));
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

		BulletManager::GetInstance()->SpawnBullet(_faction, _direction, ToWorld(localPosition), vec3(), vec3(1.7f), _faction == Faction::Player ? Player::GetInstance()->damage : 2);
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