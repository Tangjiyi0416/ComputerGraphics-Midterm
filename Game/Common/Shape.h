#pragma once
#include "../Header/Angel.h"
#include "../View.h"
#include <string.h>
#include <iostream>

class Shape
{
protected:
	vec4* _points;
	vec4* _colors;

	int _vxNumber;
	char* _vxShaderName, * _fragShaderName;
	// VAO
	GLuint _vao;
	// VBO
	GLuint _buffer;
	//  for Shader
	GLuint _shaderProgram;
	// Vertex Position Attribute
	GLuint _model, _view, _projection;
	// Matrix 
	mat4  _modelMatrix, _viewMatrix, _projectionMatrix;

	// 紀錄是否有矩陣的更新
	bool  _updateModel;
	bool  _updateView;
	bool  _updateProj;
	void CreateBufferObject();

public:
	Shape();
	virtual ~Shape();

	//virtual void Update(float dt) = 0;
	void SetShaderName(const char vxShaderName[], const char fsShaderName[]);
	void SetShader(mat4& viewMatrix = View::view, mat4& projectionMatrix = View::projection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	//void SetShader(mat4& viewMatrix = mat4(), mat4& projectionMatrix = mat4(), GLuint shaderHandle = MAX_UNSIGNED_INT);
	void setModelMatrix(mat4& mat);
	void setViewMatrix(mat4& mat);
	void setProjectionMatrix(mat4& mat);
	//void UpdateTRSMatrix();
	virtual void Draw() = 0;
	virtual void drawW() = 0;
};
