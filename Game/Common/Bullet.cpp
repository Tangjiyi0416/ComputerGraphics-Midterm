#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "TimedTextManager.h"
Bullet::Bullet(Faction faction, vec3 direction, GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_faction{ faction }, _direction{ direction }, GameObject{ parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Circle(vec3(), vec3(), vec3(2.f));
	_shapes[0]->setModelMatrix(_trs);
	_moveSpeed = 500.f;
	SetDamage(1);
	//std::cout << "bulleat faction:" << (int)_faction << std::endl;
	_collider = new Collider(this, ColliderType::Bullet, vec2(localPosition.x, localPosition.y), vec2(2, 2), vec2(1.f), std::bind(&Bullet::Onhit, this, std::placeholders::_1), _faction == Faction::Player ? 0b1000 : 0b0010);
}
Bullet::~Bullet()
{
	delete _collider;
}
void Bullet::Onhit(const Collider& other) {
	//std::cout << "Bullet was Hit" << std::endl;
	//std::cout << "position: " << localPosition.x << " " << localPosition.y << std::endl;

	ColliderType type = other.GetColliderType();
	ICanTakeDamage* target;
	TimedTextManager::SpawnText(std::to_string(_damage), 1, vec3(1.f, 1.f, 0.3f), vec2(localPosition.x, localPosition.y), 0.5f);
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
void Bullet::Update(float dt) {
	//Handle movement
	localPosition += dt * _moveSpeed * _direction;
	UpdateTRSMatrix();
	if (localPosition.y >= SCREEN_HEIGHT / 2) {
		_disabled = true;
		return;
	}
	_shapes[0]->setModelMatrix(_trs);
	_collider->SetPosition(localPosition.x, localPosition.y);
	_collider->UpdateRegion();

}

void Bullet::Draw() {
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

void Bullet::SetDamage(GLint damage)
{
	_damage = damage;
	if (_damage >= 3) {
		_shapes[0]->SetColor(vec4(1.f, 0, 0, 1.f));
	}
	else if (_damage >= 2) {
		_shapes[0]->SetColor(vec4(0.6f, 0.6f, 0, 1.f));
	}
}
