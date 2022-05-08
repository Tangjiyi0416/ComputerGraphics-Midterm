#include "Text.h"
std::map<GLchar, Text::Character> Text::_characters = std::map<GLchar, Text::Character>();
GLuint Text::_vao = 0, Text::_buffer = 0;
GLuint Text::_shaderProgram = 0;
mat4 Text::_projectionMatrix = mat4();
Text::Text(std::string text, vec3 color, GLfloat x, GLfloat y, GLfloat scale)
{
	_text = text;
	_color = color;
	_x = x;
	_y = y;
	_scale = scale;
}

Text::~Text()
{
}

void Text::Init(const char* fontPath, const mat4& projectionMatrix) {
#pragma region ft2_testing_init

	// compile and setup the shader
	// ----------------------------
	_shaderProgram = InitShader("vsText.glsl", "fsText.glsl");
	//std::cout << "Text:" << _shaderProgram << std::endl;

	_projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "projection"), 1, GL_FALSE, _projectionMatrix);

	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	// find path to font
	std::string font_name = fontPath;
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			_characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_buffer);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//*/
#pragma endregion

}
void Text::ChangeText(const std::string &text) {
	_text = text;
}
void Text::Draw()
{

	// OpenGL state
	// ------------
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	// activate corresponding render state	
	glUseProgram(_shaderProgram);
	//std::cout << _shaderProgram << std::endl;
	glUniform3f(glGetUniformLocation(_shaderProgram, "textColor"), _color.x, _color.y, _color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	// iterate through all characters
	std::string::const_iterator c;
	GLfloat x = _x, y = _y;
	for (c = _text.begin(); c != _text.end(); c++)
	{
		Character ch = _characters[*c];

		float xpos = x + ch.bearing.x * _scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * _scale;

		float w = ch.size.x * _scale;
		float h = ch.size.y * _scale;
		// update _buffer for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of _buffer memory
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * _scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);//I guess this line clears the binding to text vertex array, maybe i should do this right after I Draw anything? IDK.
	glBindTexture(GL_TEXTURE_2D, 0);//IDK what this does, same as above i guess?

	// OpenGL state, the guide didn't tell me to do this, but I do seen others disable the rules after they finished the task.
	//glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
}