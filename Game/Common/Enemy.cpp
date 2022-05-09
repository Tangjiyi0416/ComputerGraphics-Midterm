#include "Enemy.h"

Enemy::Enemy(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_collider{ nullptr },
	GameObject{ parent, localPosition, localRotation, localScale
}
{
}

Enemy::~Enemy()
{
	delete _collider;
}
void Enemy::Update(float dt) {

	//Handle movement
	if (localPosition.y <= -SCREEN_HEIGHT / 2 - 40) {
		_disabled = true;
		return;
	}
	Move(dt);
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	if (parent != nullptr) {
		vec3 pos = ToWorld(localPosition);
		_collider->SetPosition(pos.x, pos.y);
	}
	else {
		_collider->SetPosition(localPosition.x, localPosition.y);
	}
	_collider->UpdateRegion();
	//SetPosition every child
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Update(dt);
		curChild = curChild->next();
	}
	Attack(dt);
}
void Enemy::Onhit(const Collider& other) {
	std::cout << "Enemy was Hit" << std::endl;
}
void Enemy::Move(GLfloat dt)
{
	vec3 _direction(0, -1, 0);
	/*if (InputUtilities::GetKeyState(GLUT_KEY_RIGHT, true))_direction.x += 1;
	if (InputUtilities::GetKeyState(GLUT_KEY_LEFT, true))_direction.x -= 1;
	if (InputUtilities::GetKeyState(GLUT_KEY_UP, true))_direction.y += 1;
	if (InputUtilities::GetKeyState(GLUT_KEY_DOWN, true))_direction.y -= 1;*/
	//normalize(_direction);
	localPosition += _direction * dt * _speed;
}
void Enemy::Attack(GLfloat dt)
{
}
void Enemy::OnKilled()
{
}
void Enemy::TakeDamage(int damage) {
	std::cout << "I Take: " << damage << std::endl;
	_health -= damage;
	if (_health <= 0) {
		Player::GetInstance()->AddExp(_exp);
		OnKilled();
		_disabled = true;
	}
}
void Enemy::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Draw();
		curChild = curChild->next();
	}
}