#pragma once
#include "GameObject.h"
#include "Quad.h"
class Bullet :public GameObject
{
public:
	Bullet(GameObject* parent = nullptr, const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(10.f));
	void Update(float dt);
	void Draw();
private:
	GLfloat _moveSpeed;
};
Bullet::Bullet(GameObject* parent, const vec3& position, const vec3& rotation, const vec3& scale)
	:GameObject{parent, position, rotation, scale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new Quad;;
	_shapes[0]->SetShader();
	_shapes[0]->setModelMatrix(_trs);
	_moveSpeed = 20.f;
	std::cout << "bullet spawned" << std::endl;
}

void Bullet::Update(float dt) {
	//Handle movement
	position.y += dt * _moveSpeed;
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
