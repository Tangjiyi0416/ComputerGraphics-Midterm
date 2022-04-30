#pragma once
#include "../Header/Angel.h"
#include "../View.h"
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <string>
//string for map's key
using std::string; 
//Since I think simple factory pattern is overkilld for shader instances
//, I will simply use a hashmap to store it instead, does that make sense? IDK.
using std::unordered_map;

//Just some tweaks to fix the memory leak of OpenGl Objects and infinite shaders.
//resources:
//	tl;dr, derived classes won't have their own static member without lots of work : https://stackoverflow.com/questions/1390913/are-static-variables-in-a-base-class-shared-by-all-derived-classes
//	how things work: OpenGL_1.pptx OpenGL_2.pptx, and OpenGL_3.pptx
//sidenote:
//	Maybe I can just instantiate 1 of each Shape, and change its TRS, colors, other attributes...etc right before any object want to render it?

class Shape
{
protected:
	vec4* _points;
	vec4* _colors;

	int _vxNumber;
	string _vxShaderName,  _fragShaderName;
	// VAO
	GLuint _vao;
	// VBO
	GLuint _buffer;
	//  for Shader
	static std::unordered_map<string, GLuint>_shaders;
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
	void SetShaderName(const char vxShaderName[], const char fsShaderName[]);
	void SetShader(mat4& viewMatrix = View::view, mat4& projectionMatrix = View::projection);
	//void SetShader(mat4& viewMatrix = View::view, mat4& projectionMatrix = View::projection, GLuint shaderHandle = MAX_UNSIGNED_INT);

public:
	Shape();
	virtual ~Shape();
	//virtual void Update(float dt) = 0;
	//void SetShader(mat4& viewMatrix = mat4(), mat4& projectionMatrix = mat4(), GLuint shaderHandle = MAX_UNSIGNED_INT);
	void setModelMatrix(mat4& mat);
	void setViewMatrix(mat4& mat);
	void setProjectionMatrix(mat4& mat);
	//void UpdateTRSMatrix();
	virtual void Draw() = 0;
	virtual void drawW() = 0;
};
