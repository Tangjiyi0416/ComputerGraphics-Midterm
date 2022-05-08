#include "StarShape.h"
#include <iostream>
StarShape::StarShape(vec3& position, vec3& rotation, vec3& scale)
	:Shape{ position,rotation,scale }
{
	Init();
}
StarShape::StarShape(mat4& localModelMatrix)
	: Shape{ localModelMatrix }
{
	Init();
}

void StarShape::Init() {
	_vxNumber = STAR_NUM;
	_points = new vec4[_vxNumber];
	_points[0] = vec4(-0.5f, 0.f, 0.0f, 1.0f);
	_points[1] = vec4(-0.1f, -0.1f, 0.0f, 1.0f);
	_points[2] = vec4(-0.1f, 0.1f, 0.0f, 1.0f);

	_points[3] = vec4(0.f, 0.5f, 0.0f, 1.0f);
	_points[4] = vec4(-0.1f, 0.1f, 0.0f, 1.0f);
	_points[5] = vec4(0.1f, 0.1f, 0.0f, 1.0f);

	_points[6] = vec4(0.f, -0.5f, 0.0f, 1.0f);
	_points[7] = vec4(0.1f, -0.1f, 0.0f, 1.0f);
	_points[8] = vec4(-0.1f, -0.1f, 0.0f, 1.0f);

	_points[9] = vec4(0.5f, 0.f, 0.0f, 1.0f);
	_points[10] = vec4(0.1f, 0.1f, 0.0f, 1.0f);
	_points[11] = vec4(0.1f, -0.1f, 0.0f, 1.0f);


	_points[12] = vec4(-0.1f, 0.1f, 0.0f, 1.0f);
	_points[13] = vec4(-0.1f, -0.1f, 0.0f, 1.0f);
	_points[14] = vec4(0.1f, 0.1f, 0.0f, 1.0f);
	_points[15] = vec4(0.1f, 0.1f, 0.0f, 1.0f);
	_points[16] = vec4(-0.1f, -0.1f, 0.0f, 1.0f);
	_points[17] = vec4(0.1f, -0.1f, 0.0f, 1.0f);

	_colors = new vec4[_vxNumber];
	SetColor(vec4(1.f));

	// Create and initialize a buffer object 
	CreateBufferObject();
	SetShaderName("vsShape.glsl", "fsShape.glsl");
	SetShader(typeid(StarShape).name());
}

StarShape::~StarShape() {
	//std::cout << "aa" << std::endl;
}
void StarShape::Draw()
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
	glDrawArrays(GL_TRIANGLES, 0, _vxNumber);
}

void StarShape::drawW()
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
