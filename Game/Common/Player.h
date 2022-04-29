#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "../InputUtilities.h"
#include "Shield.h"
#include "Bullet.h"
#include "MainGun.h"
class Player :public GameObject
{
public:
	Player(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Player();
	void Update(float dt);
	void Draw();
private:
	GLfloat _speed = 100.f;
	//Linklist<Bullet*> _bullets;
};
Player::Player(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Quad;
	_shapes[0]->SetShader();
	_shapes[0]->setModelMatrix(_trs);
	_children.pushBack(new Shield(this, vec3(), vec3(), vec3(2.f)));
	_children.pushBack(new MainGun(this, vec3(), vec3(), vec3(.5f)));
}

Player::~Player()
{
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
	localPosition += _direction;
	UpdateTRSMatrix();
	_shapes[0]->setModelMatrix(_trs);

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
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Draw();
		curChild = curChild->next();
	}
}