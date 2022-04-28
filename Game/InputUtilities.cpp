#include "InputUtilities.h"
#include <iostream>
namespace InputUtilities {
	namespace {
		bool _keyState[TOTAL_KEY_NUMBER] = {};
		bool mouseButtonState[3] = {};
		int mousePosition[2] = {};
		void Win_MouseButton(int button, int state, int x, int y) {
			switch (button) {
			case GLUT_LEFT_BUTTON:   //LMB Event
				if (state == GLUT_DOWN) {  // pressed
					mouseButtonState[0] = true;
				}
				else if (state == GLUT_UP)
				{
					mouseButtonState[0] = false;
				}
				break;
			case GLUT_MIDDLE_BUTTON:  // ヘ玡琌菲公い龄 传Θ Y 禸
				if (state == GLUT_DOWN) {
					mouseButtonState[1] = true;
				}
				else if (state == GLUT_UP)
				{
					mouseButtonState[1] = false;
				}
				break;
			case GLUT_RIGHT_BUTTON:   // ヘ玡琌菲公龄
				if (state == GLUT_DOWN) { // ヘ玡琌菲公龄传Θ Z 禸
					mouseButtonState[2] = true;
				}
				else if (state == GLUT_UP)
				{
					mouseButtonState[2] = false;
				}
				break;
			default:
				break;
			}
		}
		void Win_MouseMotion(int x, int y) {
			mousePosition[0] = x;
			mousePosition[1] = y;
			//std::cout << mousePosition[0] << ' ' << mousePosition[1] << std::endl;
		}
		void Win_KeyboardDown(unsigned char key, int x, int y) {
			_keyState[key] = true;
		}
		void Win_KeyboardUp(unsigned char key, int x, int y) {
			_keyState[key] = false;
		}
		int GetSpecialKeyIndex(int specialKey) {
			if (specialKey > 0 && specialKey < 13) return specialKey = 127 + specialKey;
			else if (specialKey > 99 && specialKey < 109) return specialKey = 40 + specialKey;
			else return -1;
		}
		void Win_SpecialKeyboardDown(int key, int x, int y) {
			//std::cout << key << std::endl;
			key = GetSpecialKeyIndex(key);
			if (key < 0) return;
			_keyState[key] = true;
		}
		void Win_SpecialKeyboardUp(int key, int x, int y) {
			//std::cout << key << std::endl;

			key = GetSpecialKeyIndex(key);
			if (key < 0) return;
			_keyState[key] = false;
		}
	}

	void Init() {
		glutMouseFunc(Win_MouseButton);
		glutMotionFunc(Win_MouseMotion);
		glutPassiveMotionFunc(Win_MouseMotion);
		glutKeyboardFunc(Win_KeyboardDown);	// 矪瞶 ASCI 龄 AaESC 龄...单单
		glutKeyboardUpFunc(Win_KeyboardUp);
		glutSpecialFunc(Win_SpecialKeyboardDown);	// 矪瞶 NON-ASCI 龄 F1Homeよ龄...单单
		glutSpecialUpFunc(Win_SpecialKeyboardUp);
	}


	bool GetKeyState(int key, bool special) {
		if (special) key = GetSpecialKeyIndex(key);
		if (key < 0) return false;
		return _keyState[key];
	}

	bool GetMouseButtonState(int button) {
		return mouseButtonState[button];
	}
	void GetMousePosition(int& x, int& y) {
		x = mousePosition[0];
		y = mousePosition[1];
	}
}