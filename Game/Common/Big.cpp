#include "Big.h"
Big::Big(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:Enemy(parent, localPosition, localRotation, localScale)
{
	_speed = 20.f;
	_exp = 5;
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, 0, 0), vec3(0, 0, 180), vec3(2.f, 2.f, 1.f));
	_shapes[0]->SetColor(vec4(1.0f, 0.2f, 0.3f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_gun = new MainGun(Faction::Enemy, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f));
	_children.pushBack(_gun);
	_collider = new Collider(static_cast<GameObject*>(this), ColliderType::Enemy, vec2(localPosition.x, localPosition.y), vec2(1.414f, 1.2071f), vec2(localScale.x * 1.f, localScale.y * 1.f), std::bind(&Big::Onhit, this, std::placeholders::_1), 0b1);

}

Big::~Big()
{
}

void Big::Attack(GLfloat dt)
{
	if (_shots == 0 && _attackTimer >= 2) {
		//std::cout << "a1" << std::endl;
		_shots = 8;
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

void Big::Onhit(const Collider& other)
{
	//std::cout << "Big was Hit" << std::endl;
}