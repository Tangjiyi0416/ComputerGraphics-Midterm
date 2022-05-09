#pragma once
#include "GameObject.h"
#include "Triangle.h"
#include "Lens.h"
#include "../InputUtilities.h"
#include "Shield.h"
//#include "MainGun.h"
#include "Collider.h"
#include <functional>
#include "ICanTakeDamage.h"
#include "TimedTextManager.h"
#include "SecGun.h"
//#include "Boss0.h"
//class MainGun;
class SecGun;
class Player :public GameObject, public ICanTakeDamage
{
public:
	~Player();
	void TakeDamage(int damage);
	void Update(float dt);
	void Draw();
	GLuint GetTotalExp() { return _totalExp; }
	void AddExp(GLuint e) { _exp += e; _totalExp += e; }
	void AddShield(GLuint number) { _shield->AddShield(number); }
	static Player* GetInstance() {
		if (_instance == nullptr)
			_instance = new Player(nullptr, vec3(), vec3(), vec3(12.f));
		return _instance;
	}
	void SetColor(vec4 color) {
		_shapes[1]->SetColor(color);
	}
	GLint damage=1;
	bool GetUpgradeTextShow() { return _utextShow; }
	Text* GetUpgradeText() { return _uText; }
	bool _canMissile = false;
private:
	Player(GameObject* parent = nullptr, const vec3& localPosition = vec3(), const vec3& localRotation = vec3(), const vec3& localScale = vec3(1.f));
	static Player* _instance;
	GLint _health = 1;
	GLfloat _speed = 180.f;
	GLuint _exp;
	GLuint _totalExp;
	Collider* _collider;
	Shield* _shield;
	//Linklist<MainGun*> _guns;
	Linklist<SecGun*> _guns;
	float _counter = 0;
	void Onhit(const Collider&);
	//Linklist<Bullet*> _bullets;
		
	//ugly upgrades
	GLuint _threshold=20;
	bool _utextShow = false;
	int _uCount=0;
	Text* _uText;
	int _missileCounter=0;
	//hit effect red
};
