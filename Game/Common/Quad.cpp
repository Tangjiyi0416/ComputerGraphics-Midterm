#include "Quad.h"
#include <iostream>
Quad::Quad(vec3& position, vec3& rotation, vec3& scale)
	:Shape{ position,rotation,scale }
{
	Init();
}
Quad::Quad(mat4& localModelMatrix)
	: Shape{ localModelMatrix }
{
	Init();
}

void Quad::Init() {
	_vxNumber = QUAD_NUM;
	_points = new vec4[_vxNumber];
	_points[0] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_points[2] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	_points[1] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_points[3] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_points[5] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_points[4] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	_colors = new vec4[_vxNumber];
	_colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_colors[2] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[1] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[5] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_colors[4] = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	SetShaderName("vsShape.glsl", "fsShape.glsl");
	SetShader(typeid(Quad).name());
}

Quad::~Quad() {
	//std::cout << "aa" << std::endl;
}
void Quad::Draw()
{
	GLuint curShader;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&curShader);
	if(curShader!=_shaderProgram) 
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

void Quad::drawW()
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

//void Quad::SetPosition(float dt) {
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