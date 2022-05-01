#pragma once
#include "../Header/Angel.h"
#include <map>	
#include "ft2build.h"
#include FT_FREETYPE_H

//Really basic text rendering object - encapsulated(partially) for later use
//resources:
//	vcpkg for freetype-gl: https://ithelp.ithome.com.tw/articles/10221612
//	CMake for freetype-gl: https://ithelp.ithome.com.tw/articles/10221168
//	Someone that reminds be about the PATH stuff: https://github.com/jpbruyere/vkvg/issues/36
//  Doxygen for IDK Docs?: https://www.doxygen.nl/download.html
//	Text Rendering: https://learnopengl.com/In-Practice/Text-Rendering
//conclusion:
//	It works. (?
//TODO: 
// Make TextRenderer separated from Text.
// Cache TextTexture 
class Text
{
private:
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		unsigned int textureID; // ID handle of the glyph texture
		vec2   size;      // size of glyph
		vec2   bearing;   // Offset from baseline to left/top of glyph
		unsigned int advance;   // Horizontal offset to advance to next glyph
	};
	static std::map<GLchar, Character> _characters;
	static GLuint _vao, _buffer;
	static GLuint _shaderProgram;
	static mat4 _projectionMatrix;

	std::string _text;
	vec3 _color;
	GLfloat _x, _y;
	GLfloat _scale;

public:
	Text(std::string text = "", vec3 color = vec3(), GLfloat x = 0.f, GLfloat y = 0.f, GLfloat scale = 1.f);
	~Text();
	static void Init(const char* fontPath, const mat4& projectionMatrix);
	void ChangeText(const std::string &text);
	void Draw();
};
