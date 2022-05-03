#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "Lens.h"
#include "../InputUtilities.h"
#include "Shield.h"
#include "Bullet.h"
#include "MainGun.h"
#include "Collider.h"
#include <functional>
class Player :public GameObject
{
public:
	Player(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	~Player();
	void Update(float dt);
	void Draw();
private:
	GLfloat _speed = 180.f;
	Collider* collider;
	void Onhit();
	//Linklist<Bullet*> _bullets;
};
Player::Player(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 2;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Quad(vec3(0, 0, 0), vec3(), vec3(2.f, 5.f, 1.f));
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));
	_shapes[1] = new Lens(vec3(0.f, .75f, 0), vec3(), vec3(1.f));
	_shapes[1]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_children.pushBack(new Shield(this, vec3(), vec3(), vec3(2.5f)));
	_children.pushBack(new MainGun(this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f)));
	collider = new Collider(vec2(0, 0), vec2(2, 5), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Player::Onhit, this), 0100);
}

Player::~Player()
{
	delete collider;
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
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	collider->SetPosition(localPosition.x, localPosition.y);
	collider->UpdateRegion();
	//SetPosition every child
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Update(dt);
		curChild = curChild->next();
	}
}
void Player::Onhit() {
	std::cout << "Player was Hit" << std::endl;
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