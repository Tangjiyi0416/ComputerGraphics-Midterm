#include "Boss1.h"
Boss1::Boss1(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_exp = 10;
	_health = 110;
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, 0, 0), vec3(0, 0, 180), vec3(5, 5, 0));
	_shapes[0]->SetColor(vec4(1.0f, 0.7f, 0.2f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	//_children.pushBack(new MainGun(Faction::Enemy, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f)));
	_children.pushBack(new Boss2(this, vec3(0.7071f, -0.5f, 0)));
	_children.pushBack(new Boss2(this, vec3(-0.7071f, -0.5f, 0)));
	_collider = new Collider(this, ColliderType::Enemy, vec2(localPosition.x, localPosition.y), vec2(5, 5), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Boss1::Onhit, this, std::placeholders::_1), 0b1);
}

Boss1::~Boss1()
{
}

void Boss1::Move(GLfloat dt)
{
	if (parent == nullptr) {
		if (_moveTimer >= 2) {
			_moveTimer -= 2;
		}
		_moveTimer += dt;

		vec3 _direction = vec3(cos(_moveTimer * M_PI),0, 0);
		//normalize(_direction);

		_direction *= dt * _speed;
		localPosition += _direction;
	}

}

void Boss1::Onhit(const Collider& other)
{
	std::cout << "boss1 was Hit" << std::endl;
}