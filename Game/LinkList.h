#pragma once

//for whatTheheckIsGoingOn -> check LinkList.cpp
template <typename T>class Linklist;

template <typename T>
class ListNode
{
	friend class Linklist<T>;
private:
	ListNode<T>* _prev;
	ListNode<T>* _next;
public:
	T data;

	ListNode();
	ListNode(const T& data);
	~ListNode();
	ListNode<T>* next();

};

template <typename T>
class Linklist
{
private:
	ListNode<T>* _front, * _back;

public:
	Linklist();
	~Linklist();
	ListNode<T>* front();
	void pushFront(const T& item);
	void popFront();
	ListNode<T>* back();
	void pushBack(const T& item);
	void popBack();
	void remove(ListNode<T>*);
	size_t size();
	void clear();
};

