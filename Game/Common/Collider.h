#pragma once
#include "../Header/Angel.h"
#include "../LinkList.h"
#include "../View.h"
#include <functional>
#define REGION 9
//This is bad, but it works! kinda...
//resources:
//	AABB: https://davidhsu666.com/archives/gamecollisiondetection/#sat%E7%9A%84%E7%B8%BD%E7%B5%90
//	some form of delegate: https://stackoverflow.com/questions/9568150/what-is-a-c-delegate
//TODO:
// 

class Collider;
struct CollisionRegion {

	Linklist<Collider*> _enemys;
	Linklist<Collider*> _enemyBullets;
	Linklist<Collider*> _player;
	Linklist<Collider*> _playerBullets;
	vec4 _boundingBox;
};
class Collider
{
private:
	static CollisionRegion regions[REGION];
	vec4 _boundingBox;
	vec2 _size;
	vec2 _scale;
	//size_t _pointsNumber;
	//vec4* _points;
	GLubyte _layer;
	//onhit
	typedef std::function<void()> Callback;
	Callback _onHit;
public:
	void UpdateRegion();
	GLushort GetMask() { return _layer; }
	static bool CheckHit(const Collider& first, const Collider& other);
	static bool CheckHit(const vec4& first, const vec4& other);
	void SetPosition(const vec2&);
	void SetPosition(GLfloat x, GLfloat y);
	void SetSize(const vec2&);
	void SetSize(GLfloat w, GLfloat h);
	void SetScale(const vec2&);
	void SetScale(GLfloat x, GLfloat y);
	void SetOnHit(Callback onHitFunction) {
		_onHit = onHitFunction;
	}
	Collider(vec2 localPosition, vec2 size, vec2 scale, const Callback onHitFunction = nullptr, GLubyte mask = 01111);
	~Collider();
	static void Init();
	//Call after every GameObject has updated.
	static void FrameUpdate();
};

Collider::Collider(vec2 localPosition, vec2 size, vec2 scale, Callback onHitFunction, GLubyte mask) :
	_onHit{ onHitFunction },
	_layer{ mask }
{
	SetPosition(localPosition);
	SetSize(size);
	SetScale(scale);
	UpdateRegion();
}

Collider::~Collider()
{
}
void Collider::UpdateRegion() {
	for (size_t i = 0; i < REGION; i++)
	{
		if (CheckHit(_boundingBox, regions[i]._boundingBox)) {
			if (_layer & 1) regions[i]._enemys.pushBack(this);
			if (_layer & 2) regions[i]._enemyBullets.pushBack(this);
			if (_layer & 4) regions[i]._player.pushBack(this);
			if (_layer & 8) regions[i]._playerBullets.pushBack(this);
		}
	}
}
void Collider::SetPosition(const vec2& colliderPosition) {
	_boundingBox.x = colliderPosition.x;
	_boundingBox.y = colliderPosition.y;
}
void Collider::SetPosition(GLfloat x, GLfloat y) {
	_boundingBox.x = x;
	_boundingBox.y = y;
}

void Collider::SetSize(const vec2& colliderSize) {
	_size.x = colliderSize.x;
	_size.y = colliderSize.y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetSize(GLfloat w, GLfloat h) {
	_size.x = w;
	_size.y = h;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetScale(const vec2& colliderScale) {
	_scale.x = colliderScale.x;
	_scale.y = colliderScale.y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetScale(GLfloat x, GLfloat y) {
	_scale.x = x;
	_scale.y = y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}

CollisionRegion Collider::regions[9] = {};
void Collider::Init() {
	for (size_t i = 0; i < REGION; i++)
	{
		regions[i]._boundingBox = {
			(i % 3) * SCREEN_WIDTH / 3.f
			, (i / 3) * SCREEN_HEIGHT / 3.f
			, SCREEN_WIDTH / 3.f
			, SCREEN_HEIGHT / 3.f
		};

	}
}
bool Collider::CheckHit(const Collider& first, const Collider& other) {
	if (first._boundingBox.x + first._boundingBox.z / 2 > other._boundingBox.x - other._boundingBox.z / 2 &&
		other._boundingBox.x + other._boundingBox.z / 2 > first._boundingBox.x - first._boundingBox.z / 2 &&
		first._boundingBox.y + first._boundingBox.w / 2 > other._boundingBox.y - other._boundingBox.w / 2 &&
		other._boundingBox.y + other._boundingBox.w / 2 > first._boundingBox.y - first._boundingBox.w / 2
		)
		return true;
	return false;
}
bool Collider::CheckHit(const vec4& first, const vec4& other) {
	if (first.x + first.z / 2 > other.x - other.z / 2 &&
		other.x + other.z / 2 > first.x - first.z / 2 &&
		first.y + first.w / 2 > other.y - other.w / 2 &&
		other.y + other.w / 2 > first.y - first.w / 2
		)
		return true;
	return false;
}

void Collider::FrameUpdate() {
	for (size_t i = 0; i < REGION; i++)
	{
		ListNode<Collider*>* cur;

		//enemy aganist playerBullet
		cur = regions[i]._enemys.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._playerBullets.front();
			while (cur2 != nullptr)
			{
				if (CheckHit(*(cur->data), *(cur2->data))) {
					cur->data->_onHit();
					cur2->data->_onHit();
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//enemy aganist player
		cur = regions[i]._enemys.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._player.front();
			while (cur2 != nullptr)
			{
				if (CheckHit(*(cur->data), *(cur2->data))) {
					cur->data->_onHit();
					cur2->data->_onHit();
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//enemyBullet aganist player
		cur = regions[i]._enemyBullets.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._player.front();
			while (cur2 != nullptr)
			{
				if (CheckHit(*(cur->data), *(cur2->data))) {
					cur->data->_onHit();
					cur2->data->_onHit();
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//clear region for next frame
		regions[i]._enemys.clear();
		regions[i]._enemyBullets.clear();
		regions[i]._player.clear();
		regions[i]._playerBullets.clear();
	}
}