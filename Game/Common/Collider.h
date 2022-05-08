#pragma once
#include "../Header/Angel.h"
#include "../LinkList.h"
#include "../View.h"
#include "GameObject.h"
#include <functional>
#include <set>
#define REGION_V 4
#define REGION_H 4
//This is bad, but it works! kinda...
//Again..., end up gluing everything together, guess I'll try harder next time?
//resources:
//	AABB: https://davidhsu666.com/archives/gamecollisiondetection/#sat%E7%9A%84%E7%B8%BD%E7%B5%90
//	some form of delegate: https://stackoverflow.com/questions/9568150/what-is-a-c-delegate
//today I learn:
//  You cannot call a method of const reference parameter in C++, unless the method is suffix by "const":
//		https://stackoverflow.com/questions/28987916/cannot-call-a-method-of-const-reference-parameter-in-c
//	Mixed up declaration and implementation in header file is REAAAALLLLYYYY BAD
//  ,and will cause #pragma once to stop working:
//		https://stackoverflow.com/questions/1787822/why-arent-include-guards-or-pragma-once-working
// TODO:
// 

class Collider;
struct CollisionRegion {

	Linklist<Collider*> _enemys;
	Linklist<Collider*> _enemyBullets;
	Linklist<Collider*> _player;
	Linklist<Collider*> _playerBullets;
	vec4 _boundingBox;
};

enum class ColliderType {
	Player, Enemy, Bullet
};
//Simple usage guide:
//1. declare
//2. declare and implement Onhit(const Collider& other);
//3. passing it to collider's constructor
//4. pass class name by typeid(Bullet).name()
//5. updateRegion after update everything related to transform
class Collider
{
private:
	static CollisionRegion regions[REGION_V * REGION_H];
	GLushort _curRegion;
	//HACKY: colliders that may collide with this multiple times
	std::set<Collider*> _multiCollided;

	vec4 _boundingBox;
	vec2 _size;
	vec2 _scale;
	//size_t _pointsNumber;
	//vec4* _points;
	GLubyte _layer;
	//onhit
	typedef std::function<void(const Collider&)> Callback;
	Callback _onHit;
	ColliderType _colliderType;
	GameObject* _parent;
public:
	void UpdateRegion();
	GLushort GetLayer()const { return _layer; }
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
	ColliderType GetColliderType() const {
		return _colliderType;
	}
	GameObject* GetParent() const {
		return _parent;
	}

	Collider(GameObject* parent, ColliderType colliderType, vec2 localPosition, vec2 size, vec2 scale, const Callback onHitFunction = nullptr, GLubyte mask = 0B1111);
	~Collider();
	static void Init();
	//Call after every GameObject has updated.
	static void FrameUpdate();
};
