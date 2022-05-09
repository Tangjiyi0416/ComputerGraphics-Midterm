#include "Missile.h"
#include "Enemy.h"
#include "Player.h"
#include "TimedTextManager.h"
Missle::Missle(Faction faction, GLint damage, GameObject* target, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ faction }, _target{ target }, _track{ 2 }, _direction{ 0 }, GameObject{ parent = nullptr, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Lens(vec3(), vec3(), vec3(12.f, 24.f, 1.f));
	_shapes[0]->setModelMatrix(_trs);
	_moveSpeed = 90.f;
	//std::cout << "bulleat faction:" << (int)_faction << std::endl;
	_collider = new Collider(this, ColliderType::Bullet, vec2(localPosition.x, localPosition.y), vec2(12, 12), vec2(1.f), std::bind(&Missle::Onhit, this, std::placeholders::_1), _faction == Faction::Player ? 0b1000 : 0b0010);
	_damage = damage;
	if (_damage >= 3) {
		_shapes[0]->SetColor(vec4(1.f, 0, 0, 1.f));
	}
	else if (_damage == 2) {
		_shapes[0]->SetColor(vec4(1.f, 1.f, 0, 1.f));
	}
}
Missle::~Missle()
{
	delete _collider;
}
void Missle::Onhit(const Collider& other) {
	//std::cout << "Bullet was Hit" << std::endl;
	//std::cout << "position: " << localPosition.x << " " << localPosition.y << std::endl;

	ColliderType type = other.GetColliderType();
	ICanTakeDamage* target;
	TimedTextManager::SpawnText(std::to_string(_damage), 1, vec3(1.f, 1 - 0.15f * _damage, 1 - 0.33f * _damage), vec2(localPosition.x, localPosition.y), 0.5f);
	switch (type)
	{
	case ColliderType::Player:
		target = static_cast <Player*> (other.GetParent());
		target->TakeDamage(_damage);
		break;
	case ColliderType::Enemy:
		target = static_cast<Enemy*> (other.GetParent());
		target->TakeDamage(_damage);
		break;
	case ColliderType::Bullet:
		break;
	default:
		break;
	}
	_disabled = true;
}
void Missle::Update(float dt) {
	//Handle movement
	if (_track > 0) {
		_direction = ToWorld(_target->localPosition) - localPosition;
		vec2 v = normalize(vec2(_direction.x, _direction.y));
		_direction = vec3(v.x, v.y, 0);

		//std::cout << atan(_direction.y / _direction.x) << std::endl;
	}
	_track -= dt;
	localPosition += dt * _moveSpeed * _direction;
	_moveSpeed += 50.f*dt;
	UpdateTRSMatrix();
	if (localPosition.y >= SCREEN_HEIGHT / 2 || localPosition.y <= -SCREEN_HEIGHT / 2 - 40) {
		_disabled = true;
		return;
	}
	if (_direction.x != 0)
		_shapes[0]->setModelMatrix(_trs * RotateZ(90.f + 180.f * atan((double)_direction.y / _direction.x) / M_PI));
	else
		_shapes[0]->setModelMatrix(_trs);
	_collider->SetPosition(localPosition.x, localPosition.y);
	_collider->UpdateRegion();

}

void Missle::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
	ListNode<GameObject*>* cur = _children.front();
	while (cur != nullptr) {
		cur->data->Draw();
		cur = cur->next();
	}
}