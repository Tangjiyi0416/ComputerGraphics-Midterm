#include "RotateGun.h"

RotateGun::RotateGun(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ Faction::Enemy }, GameObject{
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

}

RotateGun::~RotateGun()
{
}
bool RotateGun::Shoot()
{
	if (_curCooldown <= 0) {
		vec3 _direction = Player::GetInstance()->localPosition - ToWorld(localPosition);
		vec2 v = normalize(vec2(_direction.x, _direction.y));
		_direction = vec3(v.x, v.y, 0);
		//std::cout << v.x <<" "<< v.y << std::endl;
		BulletManager::GetInstance()->SpawnBullet(_faction, _direction, ToWorld(localPosition));
		_curCooldown = _cooldown;
		return true;
	}
	return false;
}
void RotateGun::Update(float dt) {
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}

	_curCooldown -= dt;
}

void RotateGun::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
}