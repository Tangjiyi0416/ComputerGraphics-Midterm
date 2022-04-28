#pragma once
#include "../Header/Angel.h"
class Collider
{
private:
	vec4 _boundingBox;
	//size_t _pointsNumber;
	//vec4* _points;
public:
	bool CheckHit(const Collider& other);
	Collider(vec2, vec2);
	~Collider();
};

Collider::Collider(vec2 localPosition, vec2 size)
{
	_boundingBox = { localPosition.x,localPosition.y,size.x,size.y };
}

Collider::~Collider()
{
}

bool Collider::CheckHit(const Collider& other) {
	if (_boundingBox.x + _boundingBox.z > other._boundingBox.x &&
		other._boundingBox.x + other._boundingBox.z > _boundingBox.x &&
		_boundingBox.y + _boundingBox.w > other._boundingBox.y &&
		other._boundingBox.y + other._boundingBox.w > _boundingBox.y
		)
		return true;
	return false;
}