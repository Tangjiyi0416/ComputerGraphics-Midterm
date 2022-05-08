#pragma once
#include "../LinkList.h"
#include "Text.h"
#include "../Header/Angel.h"
#include <string>
//Currently not part of GameObject&Shape System
//TODO: Intergate all Text stuff into Shape and make Text a GameObject derived
using std::string;
class TimedTextManager
{
private:
	struct TimedTextObject {
		Text* text = nullptr;
		GLfloat time = 3;
		TimedTextObject(string text, GLfloat time, vec3 color, vec2 position, GLfloat scale);
		~TimedTextObject();
	};
	TimedTextManager();
	~TimedTextManager();
	static TimedTextManager* _instance;
	static Linklist<TimedTextObject*> _texts;
public:
	static TimedTextManager* GetInstance();
	static void SpawnText(string str, GLfloat time, vec3 color, vec2 position = vec2(), GLfloat scale = 1.f);
	static void Update(float delta);
	static void Draw();
};