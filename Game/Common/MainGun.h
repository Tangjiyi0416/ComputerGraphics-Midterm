#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "../InputUtilities.h"
#include "Bullet.h"

class MainGun :public GameObject
{
public:
	MainGun(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(.5f));
	~MainGun();
	void Update(float dt);
	void Draw();
private:
	GLfloat _speed = 100.f;
	Linklist<Bullet*> _bullets;
};
MainGun::MainGun(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Quad;
}

MainGun::~MainGun()
{
	while (_bullets.front() != nullptr) delete _bullets.front()->data, _bullets.popFront();
}
void MainGun::Update(float dt) {
	UpdateTRSMatrix();
	_shapes[0]->setModelMatrix(_trs);

	//Shoot
	if (InputUtilities::GetKeyState(' ')) {
		_bullets.pushBack(new Bullet(nullptr, ToWorld(localPosition)));

	}
	//Update bullets
	ListNode<Bullet*>* curBullet = _bullets.front();
	while (curBullet != nullptr) {
		if (curBullet != nullptr) {

		curBullet->data->Update(dt);
		}
		if (curBullet->data->localPosition.y >= SCREEN_HEIGHT / 2 - 40.f) {
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

void MainGun::Draw() {
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