#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "../InputUtilities.h"
#include "Shield.h"
#include "Bullet.h"

class Player :public GameObject
{
public:
	Player(GameObject* parent = nullptr, const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(1.f));
	~Player();
	void Update(float dt);
	void Draw();
private:
	GLfloat _speed = 100.f;
	Linklist<Bullet*> _bullets;
};
Player::Player(GameObject* parent, const vec3& position, const vec3& rotation, const vec3& scale)
	:GameObject{ parent, position, rotation, scale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Quad;
	_shapes[0]->SetShader();
	_children.pushBack(new Shield(this, vec3(), vec3(), vec3(2.f)));
}

Player::~Player()
{
	while (_bullets.front() != nullptr) delete _bullets.front()->data, _bullets.popFront();
}
void Player::Update(float dt) {

	//Handle movement
	vec3 _direction;
	if (InputUtilities::GetKeyState('d') || InputUtilities::GetKeyState('D'))_direction.x += 1;
	if (InputUtilities::GetKeyState('a') || InputUtilities::GetKeyState('A'))_direction.x -= 1;
	if (InputUtilities::GetKeyState('w') || InputUtilities::GetKeyState('W'))_direction.y += 1;
	if (InputUtilities::GetKeyState('s') || InputUtilities::GetKeyState('S'))_direction.y -= 1;
	normalize(_direction);
	_direction *= dt * _speed;
	position += _direction;
	UpdateTRSMatrix();
	_shapes[0]->setModelMatrix(_trs);


	//Shoot
	if (InputUtilities::GetKeyState(' ')) {
		_bullets.pushBack(new Bullet(nullptr, position));

	}
	//Update bullets
	ListNode<Bullet*>* curBullet = _bullets.front();
	while (curBullet != nullptr) {
		curBullet->data->Update(dt);
		if (curBullet->data->position.y >= SCREEN_HEIGHT / 2-40.f) {
			delete curBullet->data;
			ListNode<Bullet*>* nextBullet = curBullet->next();
			_bullets.remove(curBullet);
			curBullet = nextBullet;
		}
		else {
			curBullet = curBullet->next();
		}
	}

	//Update every child
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Update(dt);
		curChild = curChild->next();
	}
}

void Player::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}

	ListNode<Bullet*>* curBullet = _bullets.front();
	while (curBullet != nullptr) {
		curBullet->data->Draw();
		curBullet = curBullet->next();
	}

	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Draw();
		curChild = curChild->next();
	}
}