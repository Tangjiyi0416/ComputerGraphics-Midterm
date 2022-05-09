#include "Boss0.h"
Boss0* Boss0::_instance=nullptr;
Boss0::Boss0(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_exp = 50;
	_health = 120;
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, 0, 0), vec3(0, 0, 180), vec3(10, 10, 1));
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_gun = new BossGunMount(3, this);
	_children.pushBack(_gun);
	//GameObject::g_worldObjects.pushBack(new Boss1(this, vec3(7.071f, -5.f, 0)));
	//GameObject::g_worldObjects.pushBack(new Boss1(this, vec3(-7.071f, -5.f, 0)));
	_collider = new Collider(this, ColliderType::Enemy, vec2(localPosition.x, localPosition.y), vec2(10, 8.66), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Boss0::Onhit, this, std::placeholders::_1), 0b1);
	_dests[0] = vec3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 0);
	_dests[1] = vec3(SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 3, 0);
	_dests[2] = vec3(-SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 0);
	_dests[3] = vec3(-SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 3, 0);
}

Boss0::~Boss0()
{
}

void Boss0::Move(GLfloat dt)
{
	if (_moveTimer >= 2) {
		_moveTimer -= 2;
	}
	_moveTimer += dt;
	if (!_wp1) {
		if (localPosition.y > SCREEN_HEIGHT / 3) {

			_direction = vec3(cos(_moveTimer * M_PI), -1, 0);
		}
		else {
			_direction = vec3(0);
			_wp1 = true;
		}
	}

	//else if (_wp2) {
	//	_direction = _dests[_dest = rand() % 4] - localPosition;
	//	vec2 v = normalize(vec2(_direction.x, _direction.y));
	//	_direction = vec3(v.x, v.y, 0);

	//	_wp2 = false;
	//}
	//else if (abs(_dests[_dest].x - localPosition.x) <= 0.01f && abs(_dests[_dest].y - localPosition.y) <= 0.01f) {
	//	_wp2 = true;
	//}

	//normalize(_direction);

	_direction *= dt * _speed;
	localPosition += _direction;
}

void Boss0::Attack(GLfloat dt)
{
	if (_shots == 0 && _attackTimer >= 4) {
		//std::cout << "a1" << std::endl;
		_shots = 20;
		_attackTimer = 0;
	}
	else if (_shots) {
		_shots -= _gun->Shoot();
	}
	else {
		_attackTimer += dt;
	}
}
void Boss0::Onhit(const Collider& other)
{
	if (other.GetColliderType() == ColliderType::Player) {
		TimedTextManager::SpawnText("Hit!", 1, vec3(0.4f, 1.f, 0.3f), vec2(localPosition.x - 10.f, localPosition.y + 10), 0.5f);
		TimedTextManager::SpawnText("10", 1, vec3(1.f, 0.f, 0.f), vec2(localPosition.x - 10.f, localPosition.y), 0.5f);

		Player::GetInstance()-> _canMissile= true;
		Player::GetInstance()->TakeDamage(10);
		//_disabled = true;
	}
	//std::cout << "boss0 was Hit" << std::endl;
}

void Boss0::OnKilled()
{
	for (size_t i = 0; i < 10; i++)
	{
		GLfloat theta = M_PI * ((double)i / 10.f + 1.f);
		BulletManager::GetInstance()->SpawnMissile(Faction::Enemy, Player::GetInstance(), vec3(localPosition.x + cos(theta) * 70, localPosition.y - sin(theta) * 70, 0), vec3(), vec3(1.f), 5);
	}
	//while (_children.front() != nullptr)
	//{
	//	_children.front()->data->MoveObjectToWorld();
	//	_children.popFront();
	//}

}
