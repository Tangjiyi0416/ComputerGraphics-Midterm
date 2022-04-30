#pragma once
#include "GameObject.h"
#include "Circle.h"
class Bullet :public GameObject
{
public:
	Bullet(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(10.f));
	~Bullet() {};
	void Update(float dt);
	void Draw();
private:
	GLfloat _moveSpeed;
};
Bullet::Bullet(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Circle;
	_shapes[0]->setModelMatrix(_trs);
	_moveSpeed = 50.f;
	//std::cout << "bullet spawned" << std::endl;
}

void Bullet::Update(float dt) {
	//Handle movement
	localPosition.y += dt * _moveSpeed;
	UpdateTRSMatrix();

	_shapes[0]->setModelMatrix(_trs);
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
