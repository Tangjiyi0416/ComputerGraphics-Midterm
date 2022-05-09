#include "GameObject.h"
 Linklist<GameObject*> GameObject::g_worldObjects;

GameObject::GameObject(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale) :
	localPosition{ localPosition },
	localRotation{ localRotation },
	localScale{ localScale },
	parent{ parent },
	_shapesNumber{ 0 },
	_shapes{ nullptr }
{
	UpdateTRSMatrix();
}

GameObject::~GameObject()
{
	//*
	if (_shapes != nullptr) {
		for (size_t i = 0; i < _shapesNumber; i++)
			if (_shapes[i] != nullptr) {
				//std::cout << "aaa" << std::endl;
				delete _shapes[i];
			}
		delete[]_shapes;
	}
	//*/
	while (_children.front() != nullptr) delete _children.front()->data, _children.popFront();
}

 void GameObject::MoveObjectToWorld() {
	if (parent == nullptr) return;
	localPosition = ToWorld(localRotation);
	//localRotation = ToWorld(localRotation);
	localScale = localScale*parent->localScale;
	GameObject::g_worldObjects.pushBack(this);
	parent = nullptr;
}

void GameObject::UpdateTRSMatrix() {
	_translate = Translate(localPosition);
	_rotate = RotateX(localRotation.x) * RotateY(localRotation.y) * RotateZ(localRotation.z);
	_scale = Scale(localScale);
	if (parent != nullptr)
		_trs = parent->_trs * _translate * _rotate * _scale;
	else
		_trs = _translate * _rotate * _scale;
}

