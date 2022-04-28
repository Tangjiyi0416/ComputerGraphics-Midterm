#include "GameObject.h"

GameObject::GameObject(GameObject* parent, const vec3& position, const vec3& rotation, const vec3& scale) :
	position{ position },
	rotation{ rotation },
	scale{ scale },
	parent{ parent },
	_shapesNumber{ 0 },
	_shapes{ nullptr }{
	UpdateTRSMatrix();
}

GameObject::~GameObject()
{
	if (_shapes != nullptr) {
		for (size_t i = 0; i < _shapesNumber; i++)
			if (_shapes[i] != nullptr) delete _shapes[i];
		delete[]_shapes;
	}
	while (_children.front() != nullptr) delete _children.front()->data, _children.popFront();
}

void GameObject::UpdateTRSMatrix() {
	_translate = Translate(position);
	_rotate = RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
	_scale = Scale(scale);
	if (parent != nullptr)
		_trs = parent->_trs * _translate * _rotate * _scale;
	else
		_trs = _translate * _rotate * _scale;
}

