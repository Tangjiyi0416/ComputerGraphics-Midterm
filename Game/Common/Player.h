#pragma once
#include "GameObject.h"
#include "Triangle.h"
#include "Lens.h"
#include "../InputUtilities.h"
#include "Shield.h"
#include "MainGun.h"
#include "Collider.h"
#include <functional>
#include "ICanTakeDamage.h"
#include "TimedTextManager.h"
class MainGun;
class Player :public GameObject, public ICanTakeDamage
{
public:
	~Player();
	void TakeDamage(int damage);
	void Update(float dt);
	void Draw();
	GLuint GetExp() { return _exp; }
	void AddExp(GLuint e) { _exp+=e; }
	static Player* GetInstance() {
		if (_instance == nullptr)
			_instance = new Player(nullptr, vec3(), vec3(), vec3(12.f));
		return _instance;
	}
	void SetColor(vec4 color) {
		_shapes[1]->SetColor(color);
	}
	int damage=1;
private:
	Player(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	static Player* _instance;
	GLint _health = 1;
	GLfloat _speed = 180.f;
	GLuint _exp;
	Collider* _collider;
	Shield* _shield;
	Linklist<MainGun*> _guns;
	float _counter = 0;
	void Onhit(const Collider&);
	//Linklist<Bullet*> _bullets;
		
	//ugly upgrades
	bool _u1 = false;
	bool _u2 = false;
	bool _u3 = false;

};
