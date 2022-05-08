
#include "Triangle.h"

#include <iostream>
Triangle::Triangle(vec3& position, vec3& rotation, vec3& scale)
	:Shape{ position,rotation,scale }
{
	Init();
}
Triangle::Triangle(mat4& localModelMatrix)
	: Shape{ localModelMatrix }
{
	Init();
}
void Triangle::Init() {
	_vxNumber = TRIANGLE_NUM;
	_points = new vec4[_vxNumber];
	_points[0] = vec4(0.0f, 0.3f, 0.0f, 1.0f);
	_points[1] = vec4(-0.5f, -0.566f, 0.0f, 1.0f);
	_points[2] = vec4(0.5f, -0.566f, 0.0f, 1.0f);

	_colors = new vec4[_vxNumber];
	_colors[0] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[1] = vec4(0.0f, 1.f, 0.0f, 1.0f);
	_colors[2] = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	SetShaderName("vsShape.glsl", "fsShape.glsl");
	SetShader(typeid(Triangle).name());
}
Triangle::~Triangle() {}
void Triangle::Draw()
{
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
	glDrawArrays(GL_TRIANGLES, 0, _vxNumber);
}

void Triangle::drawW()
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
