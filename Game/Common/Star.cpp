#include "Star.h"

Star::Star(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_shapesNumber = 1;
	_shapes = new Shape * [_shapesNumber];
	_shapes[0] = new StarShape(vec3(0, 0, 0), vec3());
	_shapes[0]->SetColor(vec4(0.7f, 0.7f, 0.7f, 1.0f));
	_speed = 180.f;
	_counter = rand() % 1000 / 1000.f;
	//std::cout << _counter << std::endl;
}

Star::~Star()
{
}
void Star::Update(float dt)
{
	localPosition.y -= dt * _speed;
	if (_counter >= 1)_counter -= 1;
	_shapes[0]->SetColor(vec4(0.7f, 0.7f, 0.7f, sin(_counter * M_PI)));

	_counter += dt;
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
}
void Star::Draw()
{
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
}

GLfloat Star::Bezier(GLfloat t) {
	return 0 * (1 - t) * (1 - t) + 3 * .42f * t * (1 - t) * (1 - t) + 3 * .58f * t * t * (1 - t) + 1 * t * t;
}
