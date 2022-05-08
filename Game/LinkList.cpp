#include "LinkList.h"
#include <iostream>

//This file is a mess, it's one of my (countless failure) attempt to use "template" in c++ :DeadEmote:
//resources:
//	exception handle: http://kaichig.org/pydoing/cpp/cpp-try.html
//	problem about separate template implementation from header file: https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
//	using template with "friend" key word: https://www.itread01.com/content/1547443742.html
//conclusion:
//	A good chance to pratice... 100% will use STL if I was asked to do this again...
template <typename T> ListNode<T>::ListNode() {
	_prev = nullptr;
	_next = nullptr;
	data = 0;
};
template <typename T> ListNode<T>::ListNode(const T& data) {
	_prev = nullptr;
	_next = nullptr;
	this->data = data;
};
template <typename T> ListNode<T>::~ListNode() {
	if (_prev != nullptr) {
		_prev->_next = _next;
	}
	if (_next != nullptr) {
		_next->_prev = _prev;
	}
};
template <typename T> ListNode<T>* ListNode<T>::next() {
	return _next;
};
template <typename T> Linklist<T>::Linklist() {
	_front = nullptr;
	_back = nullptr;
};
template <typename T> Linklist<T>::~Linklist() {
	clear();
};
template <typename T> ListNode<T>* Linklist<T> ::front() {
	/*try {
		if (_front == nullptr) throw "the list is empty, go check.";
	}
	catch (const char* massage) {
		std::cout << massage << std::endl;
	}*/
	return _front;
}
template <typename T> void Linklist<T> ::pushFront(const T& item) {
	ListNode<T>* front = new ListNode<T>(item);
	if (_front != nullptr) {
		_front->_prev = front;
		front->_next = _front;
	}
	else {
		_back = front;
	}
	_front = front;
}
template <typename T> void Linklist<T> ::popFront() {
	if (_front != nullptr) {
		ListNode<T>* front = _front->_next;
		delete _front;
		if (front == nullptr) {
			_front = _back = nullptr;
		}
		else {
			front->_prev = nullptr;
			_front = front;
		}
	}
}
template <typename T> ListNode<T>* Linklist<T> ::back() {
	/*try {
		if (_front == nullptr) throw "the list is empty, go check.";
	}
	catch (const char* massage) {
		std::cout << massage << std::endl;
	}*/
	return _back;
}
template <typename T> void Linklist<T> ::pushBack(const T& item) {
	ListNode<T>* back = new ListNode<T>(item);
	if (_back != nullptr) {
		_back->_next = back;
		back->_prev = _back;
	}
	else {
		_front = back;
	}
	_back = back;
}
template <typename T> void Linklist<T> ::popBack() {
	if (_back != nullptr) {
		ListNode<T>* back = _back->_prev;
		delete _back;
		if (back == nullptr) {
			_back = _front = nullptr;
		}
		else {
			back->_next = nullptr;
			_back = back;
		}
	}
}
template <typename T> void Linklist<T> ::remove(ListNode<T>* node) {
	if (node == nullptr) return;
	if (node == _front)popFront();
	else if (node == _back)popBack();
	else delete node;
}
template <typename T> size_t Linklist<T> ::size() {
	size_t size = 0;

	ListNode<T>* cur = _front;
	while (cur != nullptr)
	{
		cur = cur->_next;
		size++;
	}
	return size;
}
template <typename T> void Linklist<T> ::clear() {
	while (_front != nullptr)
	{
		ListNode<T>* cur = _front;
		_front = _front->_next;
		delete cur;
	}
	_back = nullptr;
}

//for CL to work properly, add any type when needed.
template class ListNode<int>;
template class Linklist<int>;
class GameObject;
template class ListNode<GameObject*>;
template class Linklist<GameObject*>;
class Bullet;
template class ListNode<Bullet*>;
template class Linklist<Bullet*>;
class Collider;
template class ListNode<Collider*>;
template class Linklist<Collider*>;
#include "Common/TimedTextManager.h"
template class ListNode<TimedTextManager::TimedTextObject*>;
template class Linklist<TimedTextManager::TimedTextObject*>;
class Shape;
template class ListNode<Shape*>;
template class Linklist<Shape*>;
class MainGun;
template class ListNode<MainGun*>;
template class Linklist<MainGun*>;