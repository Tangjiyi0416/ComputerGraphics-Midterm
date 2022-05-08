#include "TimedTextManager.h"
TimedTextManager* TimedTextManager::_instance = nullptr;
Linklist<TimedTextManager::TimedTextObject*> TimedTextManager::_texts;
TimedTextManager* TimedTextManager::GetInstance() {
	if (_instance == nullptr)
		_instance = new TimedTextManager;
	return _instance;
}
TimedTextManager::TimedTextManager() {

}
TimedTextManager::~TimedTextManager() {

	while (_texts.front() != nullptr) delete _texts.front()->data, _texts.popFront();
}
void TimedTextManager::SpawnText(string str, GLfloat time, vec3 color, vec2 position, GLfloat scale) {
	_texts.pushBack(new TimedTextObject(str, time, color, position, scale));

}
void TimedTextManager::Update(float delta) {
	//SetPosition bullets
	ListNode<TimedTextObject*>* curText = _texts.front();
	while (curText != nullptr) {
		TimedTextObject* text = curText->data;
		if (text->time <= 0) {
			delete text;
			ListNode<TimedTextObject*>* nextText = curText->next();
			_texts.remove(curText);
			curText = nextText;
			continue;
		}
		text->time -= delta;
		curText = curText->next();

	}
}

void TimedTextManager::Draw() {
	ListNode<TimedTextObject*>* curText = _texts.front();
	while (curText != nullptr) {
		curText->data->text->Draw();
		curText = curText->next();
	}

}
TimedTextManager::TimedTextObject::TimedTextObject(string text, GLfloat time, vec3 color, vec2 position, GLfloat scale) {
	this->text = new Text(text, color, position.x, position.y, scale);
	this->time = time;
}

TimedTextManager::TimedTextObject::~TimedTextObject() {
	delete text;
}