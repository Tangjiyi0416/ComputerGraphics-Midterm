#include "Shape.h"

Shape::Shape() :
	_points{ nullptr },
	_colors{ nullptr },
	_vxShaderName{nullptr},
	_fragShaderName{nullptr},
	_updateModel{ false },
	_updateView{ false },
	_updateProj{ false }
{
}

Shape::~Shape()
{
	//std::cout << "aaaaa" << std::endl;
	//*
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_buffer);
	//*/
	if (_points != nullptr)delete[]_points;
	if (_colors != nullptr)delete[]_colors;
	if (_vxShaderName != nullptr)delete[]_vxShaderName;
	if (_fragShaderName != nullptr)delete[]_fragShaderName;
}

void Shape::CreateBufferObject()
{
	//std::cout << "Createbuffer" << std::endl;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Create and initialize a buffer object

	glGenBuffers(1, &_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, _vxNumber * sizeof(vec4) * 2, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, _vxNumber * sizeof(vec4), _points);
	glBufferSubData(GL_ARRAY_BUFFER, _vxNumber * sizeof(vec4), _vxNumber * sizeof(vec4), _colors);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Shape::SetShaderName(const char vxShader[], const char fsShader[]) {
	_vxShaderName = new char[strlen(vxShader) + 1];
	strcpy(_vxShaderName, vxShader);
	_fragShaderName = new char[strlen(fsShader) + 1];
	strcpy(_fragShaderName, fsShader);
}

void Shape::SetShader(mat4& viewMatrix, mat4& projectionMatrix, GLuint shaderHandle)
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);

	// Load shaders and use the resulting shader program
	if (shaderHandle == MAX_UNSIGNED_INT) _shaderProgram = InitShader(_vxShaderName, _fragShaderName);
	else _shaderProgram = shaderHandle;
	std::cout << _shaderProgram << std::endl;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(_shaderProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(_shaderProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(_vxNumber * sizeof(vec4)));

	_model = glGetUniformLocation(_shaderProgram, "Model");
	_modelMatrix = mat4();
	glUniformMatrix4fv(_model, 1, GL_TRUE, _modelMatrix);

	_view = glGetUniformLocation(_shaderProgram, "View");
	_viewMatrix = viewMatrix;
	glUniformMatrix4fv(_view, 1, GL_TRUE, _viewMatrix);

	_projection = glGetUniformLocation(_shaderProgram, "Projection");
	_projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(_projection, 1, GL_TRUE, _projectionMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Shape::setModelMatrix(mat4& mat)
{
	_modelMatrix = mat;
	_updateModel = true;
}

void Shape::setViewMatrix(mat4& mat)
{
	_viewMatrix = mat;
	_updateView = true;
}

void Shape::setProjectionMatrix(mat4& mat)
{
	_projectionMatrix = mat;
	_updateProj = true;
}

//void Shape::UpdateTRSMatrix()
//{
//	_modelMatrix = parent * _localTransRotScaleMatrix;
//	_bUpdateMV = true;
//
//}
//void Shape::setColor(vec4 vColor)
//{
//	_color[0] = vColor.x; _color[1] = vColor.y;
//	_color[2] = vColor.z; _color[3] = vColor.w;
//
//	for (int i = 0; i < _vxNumber; i++) {
//		_colors[i].x = _color[0];
//		_colors[i].y = _color[1];
//		_colors[i].z = _color[2];
//		_colors[i].w = _color[3];
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
//	glBufferSubData(GL_ARRAY_BUFFER, _vxNumber * sizeof(vec4), _vxNumber * sizeof(vec4), _colors);
//}
