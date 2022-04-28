#pragma once
#include "GL/glut.h"
#define TOTAL_KEY_NUMBER 148//127(ascii)+12(F1~12)+9(arrow keys, page up/down and home/end)

namespace InputUtilities {

	void Init();
	bool GetKeyState(int key, bool special = false);
	bool GetMouseButtonState(int button);
	void GetMousePosition(int& x, int& y);

};