#include "BossGun.h"

BossGun::BossGun(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ Faction::Enemy }, GameObject{
	parent, localPosition, localRotation, localScale
}
{
	_shapesNumber = 2;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Circle;
	_shapes[1] = new Quad(vec3(0,-1,0),vec3(0),vec3(1,2,1));
	_shapes[1]->SetColor(vec4(.1f, .1f, .2f,1));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}

}

BossGun::~BossGun()
{
}
bool BossGun::Shoot()
{
	if (_curCooldown <= 0) {
		vec4 direction(0,-1,0,1);
		direction = _trs * direction;
		vec2 n(direction.x, direction.y);
		n = -normalize(n);
		//std::cout << direction.x<<" "<<direction.y << std::endl;
		BulletManager::GetInstance()->SpawnBullet(_faction, vec3(n.x, n.y,0), ToWorld(localPosition),vec3(),vec3(1.4f));
		_curCooldown = _cooldown;
		return true;
	}
	return false;
}
void BossGun::Update(float dt) {
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}

	_curCooldown -= dt;
}

void BossGun::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
}