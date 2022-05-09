#include "Medium.h"
Medium::Medium(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_speed = 30.f;
	_exp = 5;
	_shapesNumber = 2;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(-0.6f, 0, 0), vec3(0, 0, 135), vec3(2.f, 2.f, 1.f));
	_shapes[0]->SetColor(vec4(0.6f, 0.4f, 0.8f, 1.0f));
	_shapes[1] = new Triangle(vec3(0.6f, 0, 0), vec3(0, 0, 225), vec3(2.f, 2.f, 1.f));
	_shapes[1]->SetColor(vec4(0.6f, 0.4f, 0.8f, 1.0f));
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_gun = new SecGun(Faction::Enemy, this, vec3(0, 0, 0), vec3(), vec3(.5f));
	_children.pushBack(_gun);
	_collider = new Collider(static_cast<GameObject*>(this), ColliderType::Enemy, vec2(localPosition.x, localPosition.y), vec2(2.f, 1.2071f), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Medium::Onhit, this, std::placeholders::_1), 0b1);
	_destX = rand() % (SCREEN_WIDTH - 80) - (SCREEN_WIDTH - 80) / 2;
}

Medium::~Medium()
{
}

void Medium::Attack(GLfloat dt)
{
	if (_shots == 0 && _attackTimer >= 3) {
		//std::cout << "a1" << std::endl;
		_shots = 5;
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
void Medium::Move(GLfloat dt)
{
	vec3 _direction;
	if (abs(_destX - localPosition.x) > 0.01f) {

		_direction = vec3(_destX - localPosition.x, -200, 0);
		_direction *= dt * 0.3f;
	}
	else {
		_direction = vec3(0, -1, 0);
	}
	localPosition += _direction;
}
void Medium::Onhit(const Collider& other)
{
	//std::cout << "Big was Hit" << std::endl;
}