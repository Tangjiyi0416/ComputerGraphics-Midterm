#include "Sentinel.h"
Sentinel::Sentinel(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_exp = 10;
	_shapesNumber = 1;
	_health = 15;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Lens(vec3(0, 0, 0), vec3(0, 0, 180), vec3(5.f), 2);
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_gun = new RotateGun(this, vec3(0));
	_children.pushBack(_gun);
	_collider = new Collider(static_cast<GameObject*>(this), ColliderType::Enemy, vec2(0, 0), vec2(2, 5), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Sentinel::Onhit, this, std::placeholders::_1), 0b1);
	GLfloat theta = M_PI * (rand() % 101 / 100.f);
	_destination = vec3(cos(theta) * 200, sin(theta) * 150, 0);
}

Sentinel::~Sentinel()
{
}
void Sentinel::Attack(GLfloat dt)
{
	if (_shots == 0 && _attackTimer >= 2) {
		//std::cout << "a1" << std::endl;
		_shots = 4;
		_attackTimer = 0;
	}
	else if (_shots) {
		if (_gun->Shoot())
			_shots--;
	}
	else {
		_attackTimer += dt;
	}
}

void Sentinel::Move(GLfloat dt)
{
	vec3 _direction = _destination - localPosition;
	if (_direction.x > 0.01f || _direction.y > 0.01f) {

		_direction *= dt * 0.3f;
		localPosition += _direction;
	}
}

void Sentinel::Onhit(const Collider& other)
{
	//std::cout << "Sentinel was Hit" << std::endl;
}