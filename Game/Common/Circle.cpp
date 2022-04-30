
#include "Circle.h"

#include <iostream>
Circle::Circle(GLfloat radius) :_radius{ radius }
{
	_vxNumber = CIRCLE_NUM;
	_points = new vec4[_vxNumber];
	_colors = new vec4[_vxNumber];
	for (size_t i = 0; i < _vxNumber; i++)
	{
		GLfloat  theta = M_PI * 2.0f * ((double)i / _vxNumber + .25f);

		GLfloat x = _radius * cosf(theta);
		GLfloat y = _radius * sinf(theta);
		_points[i] = vec4(x, y, 0.f, 1.f);
		_colors[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	SetShaderName("vsShape.glsl", "fsShape.glsl");
	SetShader();
}
Circle::~Circle() {}
void Circle::Draw()
{
	glUseProgram(_shaderProgram);
	glBindVertexArray(_vao);
	if (_updateModel) {
		glUniformMatrix4fv(_model, 1, GL_TRUE, _modelMatrix);
		_updateModel = false;
	}
	if (_updateView) {
		glUniformMatrix4fv(_view, 1, GL_TRUE, _viewMatrix);
		_updateView = false;
	}

	if (_updateProj) {
		glUniformMatrix4fv(_projection, 1, GL_TRUE, _projectionMatrix);
		_updateProj = false;
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM);
}

void Circle::drawW()
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
	glDrawArrays(GL_TRIANGLES, 0, CIRCLE_NUM);
}
