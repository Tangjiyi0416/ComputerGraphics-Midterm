#pragma once
#include "../Header/Angel.h"
#include "Shape.h"
#include "../LinkList.h"
class GameObject
{
public:
	GameObject(GameObject* parent = nullptr, const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(1.f));
	~GameObject();
	virtual void Update(float dt) = 0;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	GameObject* parent;
	virtual void Draw() = 0;
protected:
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

