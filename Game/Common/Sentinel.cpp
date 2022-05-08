#include "Sentinel.h"
Sentinel::Sentinel(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Lens(vec3(0, 0, 0), vec3(0, 0, 180), vec3(5.f), 2);
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_children.pushBack(new MainGun(Faction::Enemy, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f)));
	_collider = new Collider(static_cast<GameObject*>(this), ColliderType::Enemy, vec2(0, 0), vec2(2, 5), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Sentinel::Onhit, this, std::placeholders::_1), 0b1);
	GLfloat theta = M_PI * (rand() % 101 / 100.f);
	_destination = vec3(cos(theta) * 100, sin(theta) * 100, 0);
}

Sentinel::~Sentinel()
{
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
	std::cout << "Small was Hit" << std::endl;
}