#pragma once
#include "GameObject.h"
#include "Quad.h"
class Shield :public GameObject
{
public:
	Shield(GameObject* parent = nullptr, const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(1.f));
	void Update(float dt);
	void Draw();
private:
	GLfloat _radius;
	GLfloat _counter;
	GLfloat _rotateSpeed;
	mat4 _shieldScaleMatrix;
};
Shield::Shield(GameObject* parent, const vec3& position, const vec3& rotation, const vec3& scale)
	:GameObject{ parent, position, rotation, scale }
{
	_shapesNumber = 10;
	_shapes = new Shape * [_shapesNumber];
	_radius = 1.f;
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i] = new Quad;
		_shapes[i]->SetShader();
		GLfloat x = _radius * cosf(M_PI * 2.0f * ((double)i / _shapesNumber + .25f));
		GLfloat y = _radius * sinf(M_PI * 2.0f * ((double)i / _shapesNumber + .25f));
		_shapes[i]->setModelMatrix(_trs * Translate(x, y, 0) * _shieldScaleMatrix);
	}
	_counter = 0;
	_rotateSpeed = 0.2f;
	_shieldScaleMatrix = Scale(0.4f);
}

void Shield::Update(float dt) {
	//Handle movement
	UpdateTRSMatrix();

	_counter += dt * _rotateSpeed;
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		GLfloat x = _radius * cosf(M_PI * 2.0f * ((double)i / _shapesNumber + _counter + .25f));
		GLfloat y = _radius * sinf(M_PI * 2.0f * ((double)i / _shapesNumber + _counter + .25f));
		_shapes[i]->setModelMatrix(_trs * Translate(x, y, 0) * _shieldScaleMatrix);
	}
	if (_counter >= 2.f) {
		_counter -= 2.f;
	}
}

void Shield::Draw() {
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