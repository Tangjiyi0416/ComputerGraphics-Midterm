#include "Lens.h"
#include <iostream>
Lens::Lens(vec3& position, vec3& rotation, vec3& scale)
	:Shape{ position,rotation,scale }
{
	Init();
}
Lens::Lens(mat4& localModelMatrix)
	: Shape{ localModelMatrix }
{
	Init();
}

void Lens::Init() {
	_radiusLeft = 0.7f;
	_radiusRight = 0.7f;
	_offsetLeft = 0.5f;
	_offsetRight = 0.5f;

	_vxNumber = LENS_NUM * 2;
	_points = new vec4[_vxNumber];
	_colors = new vec4[_vxNumber];

	GLfloat theta =
		acosf((
			(
				_radiusLeft * _radiusLeft
				- _radiusRight * _radiusRight
				- _offsetLeft * _offsetLeft
				+ _offsetRight * _offsetRight
				)
			/ 2.f
			/ (_offsetLeft + _offsetRight)
			+ _offsetLeft
			)
			/ _radiusLeft
		);
	/*
	_points[0] = vec4(cos(theta) * _radiusLeft - _offsetLeft, sin(theta) * _radiusLeft, 0, 1.f);
	_points[1] = vec4(-cos(0) * _radiusRight + _offsetRight, sin(0) * _radiusRight, 0, 1.f);
	_points[2] = vec4(cos(0) * _radiusLeft - _offsetLeft, sin(0) * _radiusLeft, 0, 1.f);
	_points[3] = vec4(-cos(-theta) * _radiusRight + _offsetRight, sin(-theta) * _radiusRight, 0, 1.f);
	*/

	for (size_t i = 0; i < LENS_NUM; i++)
	{
		_points[i] = vec4(cos(theta - 2 * i * theta / LENS_NUM) * _radiusLeft - _offsetLeft, sin(theta - 2 * i * theta / LENS_NUM) * _radiusLeft, 0, 1.f);
		std::cout << _points[i].x << ", " << _points[i].y << std::endl;

	}
	for (size_t i = LENS_NUM; i < _vxNumber; i++)
	{
		_points[i] = vec4(-cos(-3 * theta + 2 * i * theta / LENS_NUM) * _radiusRight + _offsetRight, sin(-3 * theta + 2 * i * theta / LENS_NUM) * _radiusRight, 0, 1.f);
		std::cout << _points[i].x << ", " << _points[i].y << std::endl;

	}
	/*
	_colors[0] = vec4(1, 0);
	_colors[1] = vec4(1, 0);
	_colors[2] = vec4(1, 0);
	_colors[3] = vec4(1, 0);
	*/
	for (size_t i = 0; i < _vxNumber; i++)
	{
		_colors[i] = vec4(1.f, 1.f);
	}
	// Create and initialize a buffer object 
	CreateBufferObject();
	SetShaderName("vsShape.glsl", "fsShape.glsl");
	SetShader(typeid(Lens).name());
}

Lens::~Lens() {
	//std::cout << "aa" << std::endl;
}
void Lens::Draw()
{
	GLuint curShader;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&curShader);
	if (curShader != _shaderProgram)
		glUseProgram(_shaderProgram);
	glBindVertexArray(_vao);
	//if (_updateModel) {
	glUniformMatrix4fv(_model, 1, GL_TRUE, _modelMatrix * _localModelMatrix);
	//_updateModel = false;
//}
//if (_updateView) {
	glUniformMatrix4fv(_view, 1, GL_TRUE, _viewMatrix);
	//_updateView = false;
//}

//if (_updateProj) {
	glUniformMatrix4fv(_projection, 1, GL_TRUE, _projectionMatrix);
	//_updateProj = false;
//}
	glDrawArrays(GL_TRIANGLE_FAN, 0, _vxNumber);
}

void Lens::drawW()
{
	glBindVertexArray(_vao);

	//if (_bUpdateMV) {
		//_modelViewMatrixFinal = _viewMatrix * _modelMatrix;
		//_bUpdateMV = false;
	//}
	glUniformMatrix4fv(_model, 1, GL_TRUE, _modelMatrix);
	glUniformMatrix4fv(_view, 1, GL_TRUE, _viewMatrix);
	//if (_bUpdateProj) {
	glUniformMatrix4fv(_projection, 1, GL_TRUE, _projectionMatrix);
	//_bUpdateProj = false;
//}
	glDrawArrays(GL_TRIANGLES, 0, _vxNumber);
}

//void Lens::Update(float dt) {
//
//}
/*


void CQuad::setVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
{
	_Colors[0].x = vLFColor[0];
	_Colors[0].y = vLFColor[1];
	_Colors[0].z = vLFColor[2];
	_Colors[0].w = vLFColor[3];
	_Colors[3] = _Colors[0];

	_Colors[1].x = vLRColor[0];
	_Colors[1].y = vLRColor[1];
	_Colors[1].z = vLRColor[2];
	_Colors[1].w = vLRColor[3];

	_Colors[2].x = vTRColor[0];
	_Colors[2].y = vTRColor[1];
	_Colors[2].z = vTRColor[2];
	_Colors[2].w = vTRColor[3];
	_Colors[4] = _Colors[2];

	_Colors[5].x = vTLColor[0];
	_Colors[5].y = vTLColor[1];
	_Colors[5].z = vTLColor[2];
	_Colors[5].w = vTLColor[3];

	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}
*/