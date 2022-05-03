#pragma once
#include "Collider.h"
//Whenever I need a new layer, I need to edit this file
//, this is bad, but it keeps the system simple, so not so bad after all.
class SimplePhysics
{
private:

public:
	SimplePhysics();
	~SimplePhysics();
	void CheckCollision();
	void Update();

};

SimplePhysics::SimplePhysics()
{
}

SimplePhysics::~SimplePhysics()
{
}
void SimplePhysics::CheckCollision() {
	//for (size_t i = 0; i < 9; i++)
	//{

	//	ListNode<Collider*>* cur = regions[i]._enemys.front();
	//	while (cur != nullptr) {
	//		cur->data->SetBoundingBox();
	//		cur = cur->next();
	//	}
	//}
}
