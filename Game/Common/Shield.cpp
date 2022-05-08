#include "Shield.h"

Shield::Shield(GLint shieldCount, GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_radius = 1.f;
	_rotateSpeed = 108.f;
	_shieldScaleMatrix = Scale(0.05f);
	AddShield(shieldCount);
}
Shield::~Shield() {
	while (_shieldShapes.front() != nullptr) delete _shieldShapes.front()->data, _shieldShapes.popFront();
}
void Shield::Update(float dt) {
	if (localRotation.z >= 360.f) {
		localRotation.z -= 360.f;
	}
	localRotation.z += dt * _rotateSpeed;
	//Handle movement
	UpdateTRSMatrix();

	//_counter += dt * _rotateSpeed;
	//for (size_t i = 0; i < _shapesNumber; i++)
	//{
	//	GLfloat  theta = M_PI * 2.0f * ((double)i / _shapesNumber + .25f);
	//	GLfloat x = _radius * cosf(theta);
	//	GLfloat y = _radius * sinf(theta);
	//	_shapes[i]->setModelMatrix(_trs * Translate(x, y, 0));
	//}
	// 	   	
	ListNode<Shape*>* cur = _shieldShapes.front();
	while (cur != nullptr)
	{
		cur->data->setModelMatrix(_trs);
		cur = cur->next();
	}
	//if (_counter >= 2.f) {
	//	_counter -= 2.f;
	//}

}

void Shield::Draw() {
	ListNode<Shape*>* cur = _shieldShapes.front();
	while (cur != nullptr) {
		cur->data->Draw();
		cur = cur->next();
	}
}

void Shield::AddShield(int number) {
	while (number > 0) {
		_shieldShapes.pushBack(new Circle);
		number--;
		_shieldCount++;
	}
	while (number < 0) {
		_shieldShapes.popBack();
		number++;
		_shieldCount--;
	}
	if (_shieldCount < 0)_shieldCount = 0;
	ListNode<Shape*>* cur = _shieldShapes.front();
	for (int i = 0; i < _shieldCount; i++)
	{
		GLfloat theta = M_PI * 2.0f * ((double)i / _shieldCount + .25f);
		GLfloat x = _radius * cosf(theta);
		GLfloat y = _radius * sinf(theta);
		cur->data->setLocalModelMatrix(Translate(x, y, 0) * _shieldScaleMatrix);
		cur->data->setModelMatrix(_trs);
		cur = cur->next();
	}
}