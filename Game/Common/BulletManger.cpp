#include "BulletManager.h"
BulletManager* BulletManager::_instance = nullptr;
Linklist<Bullet*> BulletManager::_bullets;
BulletManager* BulletManager::GetInstance() {
	if (_instance == nullptr)
		_instance = new BulletManager;
	return _instance;
}
BulletManager::BulletManager()
{
}

BulletManager::~BulletManager() {
	while (_bullets.front() != nullptr) delete _bullets.front()->data, _bullets.popFront();

}
void BulletManager::SpawnBullet(Faction faction,vec3 direction, vec3 position, vec3 rotation, vec3 scale) {
	_bullets.pushBack(new Bullet(faction,direction, nullptr, position, rotation, scale));
	//std::cout << "position: " << position.x << " " << position.y << std::endl;

}
void BulletManager::Update(float delta) {
	//SetPosition bullets
	ListNode<Bullet*>* curBullet = _bullets.front();
	while (curBullet != nullptr) {
		if (curBullet->data != nullptr) {
			if (curBullet->data->isDisabled()) {
				delete curBullet->data;
				ListNode<Bullet*>* nextBullet = curBullet->next();
				_bullets.remove(curBullet);
				curBullet = nextBullet;
				continue;
			}
			else {
				curBullet->data->Update(delta);
			}

		}

		curBullet = curBullet->next();

	}
}

void BulletManager::Draw() {
	ListNode<Bullet*>* curBullet = _bullets.front();
	while (curBullet != nullptr) {
		curBullet->data->Draw();
		curBullet = curBullet->next();
	}

}