#include "BossGunMount.h"

BossGunMount::BossGunMount(GLint gunCount, GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:GameObject{ parent, localPosition, localRotation, localScale }
{
	_radius = 5.f;
	_rotateSpeed = 108.f;
	AddGun(gunCount);
}
BossGunMount::~BossGunMount() {
	while (_guns.front() != nullptr) delete _guns.front()->data, _guns.popFront();
}
int BossGunMount::Shoot()
{
	int count = 0;
	ListNode<BossGun*>* cur = _guns.front();
	while (cur != nullptr)
	{
		if (cur->data->Shoot()) {
			count++;
		}
		cur = cur->next();
	}
	return count;
}
void BossGunMount::Update(float dt) {
	if (localRotation.z >= 360.f) {
		localRotation.z -= 360.f;
	}
	localRotation.z += dt * _rotateSpeed;
	//Handle movement
	UpdateTRSMatrix();

	//_counter += dt * _rotateSpeed;
	//for (size_t i = 0; i < _shapesNumber; i++)
	//{
	//	GLfloat  theta = M_PI * 2.0f * ((double)i / _shapesNumber + .25f);
	//	GLfloat x = _radius * cosf(theta);
	//	GLfloat y = _radius * sinf(theta);
	//	_shapes[i]->setModelMatrix(_trs * Translate(x, y, 0));
	//}
	// 	   	
	ListNode<BossGun*>* cur = _guns.front();
	while (cur != nullptr)
	{
		cur->data->Update(dt);
		cur = cur->next();
	}
	//if (_counter >= 2.f) {
	//	_counter -= 2.f;
	//}

}

void BossGunMount::Draw() {
	ListNode<BossGun*>* cur = _guns.front();
	while (cur != nullptr) {
		cur->data->Draw();
		cur = cur->next();
	}
}

void BossGunMount::AddGun(int number) {
	while (number > 0) {
		_guns.pushBack(new BossGun(this,vec3(0), vec3(0), vec3(2,2,0)));
		number--;
		_gunsCount++;
	}
	while (number < 0) {
		_guns.popBack();
		number++;
		_gunsCount--;
	}
	if (_gunsCount < 0)_gunsCount = 0;
	_gunsCount = 1;
	//_guns.pushBack(new BossGun(this, vec3(0, 5, 0), vec3(), vec3(5.f)));

	ListNode<BossGun*>* cur = _guns.front();
	for (int i = 0; i < _gunsCount; i++)
	{
		GLfloat theta = M_PI * 2.0f * ((double)i / _gunsCount + .25f);
		GLfloat x = _radius * cosf(theta);
		GLfloat y = _radius * sinf(theta);
		cur->data->localPosition = vec3(x, y, 0);
		cur->data->localRotation = vec3(0, 0, (90.f + theta));
		cur = cur->next();
	}
}