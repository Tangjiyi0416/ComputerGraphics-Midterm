#include "Boss0.h"
Boss0::Boss0(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, 0, 0), vec3(0, 0, 180));
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_children.pushBack(new MainGun(Faction::Enemy, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f)));
	_children.pushBack(new Boss1(this, vec3(0.7071f, -0.5f, 0)));
	_children.pushBack(new Boss1(this, vec3(-0.7071f, -0.5f, 0)));
	_collider = new Collider(static_cast<GameObject*>(this), ColliderType::Enemy, vec2(localPosition.x, localPosition.y), vec2(1, 1), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Boss0::Onhit, this, std::placeholders::_1), 0b1);

}

Boss0::~Boss0()
{
}

void Boss0::Move(GLfloat dt)
{
	if (_moveTimer >= 2) {
		_moveTimer -= 2;
	}
	_moveTimer += dt;

	vec3 _direction = vec3(cos(_moveTimer * M_PI), 0, 0);
	//normalize(_direction);

	_direction *= dt * _speed;
	localPosition += _direction;
}

void Boss0::Onhit(const Collider& other)
{
	std::cout << "Small was Hit" << std::endl;
}