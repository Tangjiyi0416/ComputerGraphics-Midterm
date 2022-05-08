#pragma once
#include "../Header/Angel.h"
#include "Shape.h"
#include "../LinkList.h"
class GameObject
{
public:

	GameObject(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	virtual ~GameObject();
	virtual void Update(float dt) = 0;
	vec3 localPosition;
	vec3 localRotation;
	vec3 localScale;
	vec3 ToWorld(vec3 vector) {
		vec4 v4(vector);
		v4 = parent->_trs * v4;
		return vec3(v4.x, v4.y, v4.z);
	}
	GameObject* parent;
	virtual void Draw() = 0;
	bool isDisabled()const { return _disabled; }
protected:
	bool _disabled = false;
	void UpdateTRSMatrix();
	size_t _shapesNumber;
	Shape** _shapes;
	mat4 _translate;
	mat4 _rotate;
	mat4 _scale;
	mat4 _trs;
	Linklist<GameObject*> _children;
	//TODO Collider
};

