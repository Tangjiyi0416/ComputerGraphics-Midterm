#include "Collider.h"
Collider::Collider(GameObject* parent, ColliderType colliderType, vec2 localPosition, vec2 size, vec2 scale, Callback onHitFunction, GLubyte mask) :
	_parent{ parent },
	_colliderType{ colliderType },
	_onHit{ onHitFunction },
	_layer{ mask },
	_curRegion{ 0 }
{
	SetPosition(localPosition);
	SetSize(size);
	SetScale(scale);
	UpdateRegion();
}

Collider::~Collider()
{
}
void Collider::UpdateRegion() {
	_curRegion = 0;
	_multiCollided.clear();
	for (size_t i = 0; i < REGION_V * REGION_H; i++)
	{
		if (CheckHit(_boundingBox, regions[i]._boundingBox)) {
			//std::cout << "in region: " << i << std::endl;
			_curRegion += 1 << i;
			if (_layer & 1) {
				regions[i]._enemys.pushBack(this);
				//std::cout << "to enemy in region: " << i << std::endl;
			}
			if (_layer & 2) {
				regions[i]._enemyBullets.pushBack(this);
				//std::cout << "to enemyBullets in region: " << i << std::endl;
			}
			if (_layer & 4) {
				regions[i]._player.pushBack(this);
				//std::cout << "to player in region: " << i << std::endl;
			}
			if (_layer & 8) {
				regions[i]._playerBullets.pushBack(this);
				//std::cout << "to playerBullets in region: " << i << std::endl;
			}
		}
	}
}
void Collider::SetPosition(const vec2& colliderPosition) {
	_boundingBox.x = colliderPosition.x;
	_boundingBox.y = colliderPosition.y;

}
void Collider::SetPosition(GLfloat x, GLfloat y) {
	_boundingBox.x = x;
	_boundingBox.y = y;
	//std::cout << _boundingBox.x << "," << _boundingBox.y << std::endl;
}

void Collider::SetSize(const vec2& colliderSize) {
	_size.x = colliderSize.x;
	_size.y = colliderSize.y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetSize(GLfloat w, GLfloat h) {
	_size.x = w;
	_size.y = h;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetScale(const vec2& colliderScale) {
	_scale.x = colliderScale.x;
	_scale.y = colliderScale.y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}
void Collider::SetScale(GLfloat x, GLfloat y) {
	_scale.x = x;
	_scale.y = y;
	_boundingBox.z = _size.x * _scale.x;
	_boundingBox.w = _size.y * _scale.y;
}

CollisionRegion Collider::regions[REGION_V * REGION_H] = {};
void Collider::Init() {
	for (size_t i = 0; i < REGION_V; i++)
	{
		for (size_t j = 0; j < REGION_H; j++)
		{

			regions[i * REGION_V + j]._boundingBox = {
				j * SCREEN_WIDTH / REGION_H + SCREEN_WIDTH / (REGION_H * 2.f) - SCREEN_WIDTH / 2.f
				, i * SCREEN_HEIGHT / REGION_V + SCREEN_HEIGHT / (REGION_V * 2.f) - SCREEN_HEIGHT / 2.f
				, SCREEN_WIDTH / REGION_H
				, SCREEN_HEIGHT / REGION_V
			};
		}

	}
}
bool Collider::CheckHit(const Collider& first, const Collider& other) {
	if (first._boundingBox.x + first._boundingBox.z / 2 > other._boundingBox.x - other._boundingBox.z / 2 &&
		other._boundingBox.x + other._boundingBox.z / 2 > first._boundingBox.x - first._boundingBox.z / 2 &&
		first._boundingBox.y + first._boundingBox.w / 2 > other._boundingBox.y - other._boundingBox.w / 2 &&
		other._boundingBox.y + other._boundingBox.w / 2 > first._boundingBox.y - first._boundingBox.w / 2
		)
		return true;
	return false;
}
bool Collider::CheckHit(const vec4& first, const vec4& other) {
	if (first.x + first.z / 2 > other.x - other.z / 2 &&
		other.x + other.z / 2 > first.x - first.z / 2 &&
		first.y + first.w / 2 > other.y - other.w / 2 &&
		other.y + other.w / 2 > first.y - first.w / 2
		)
		return true;
	return false;
}

void Collider::FrameUpdate() {
	for (size_t i = 0; i < REGION_V * REGION_H; i++)
	{
		ListNode<Collider*>* cur;

		//enemy aganist playerBullet
		cur = regions[i]._enemys.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._playerBullets.front();
			while (cur2 != nullptr)
			{
				std::set<Collider*>& curSet = cur->data->_multiCollided;
				if (curSet.find(cur2->data) == curSet.end() && CheckHit(*(cur->data), *(cur2->data))) {
					if ((cur->data->_curRegion & cur2->data->_curRegion) != 1 << i) {
						cur->data->_multiCollided.insert(cur2->data);
					}
					cur->data->_onHit(*(cur2->data));

					cur2->data->_onHit(*(cur->data));
					//std::cout << "in region: " << i << std::endl;
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//player aganist enemy
		cur = regions[i]._player.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._enemys.front();
			while (cur2 != nullptr)
			{
				std::set<Collider*>& curSet = cur->data->_multiCollided;
				if (curSet.find(cur2->data) == curSet.end() && CheckHit(*(cur->data), *(cur2->data))) {
					if ((cur->data->_curRegion & cur2->data->_curRegion) != 1 << i) {
						cur->data->_multiCollided.insert(cur2->data);
					}
					cur->data->_onHit(*(cur2->data));
					cur2->data->_onHit(*(cur->data));
					//std::cout << "in region: " << i << std::endl;
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//player aganist enemyBullet
		cur = regions[i]._player.front();
		while (cur != nullptr) {
			ListNode<Collider*>* cur2 = regions[i]._enemyBullets.front();
			while (cur2 != nullptr)
			{
				std::set<Collider*>& curSet = cur->data->_multiCollided;
				if (curSet.find(cur2->data) == curSet.end() && CheckHit(*(cur->data), *(cur2->data))) {
					if ((cur->data->_curRegion & cur2->data->_curRegion) != 1 << i) {
						cur->data->_multiCollided.insert(cur2->data);
					}
					cur->data->_onHit(*(cur2->data));
					cur2->data->_onHit(*(cur->data));
					//std::cout << "in region: " << i << std::endl;
				}
				cur2 = cur2->next();
			}
			cur = cur->next();
		}
		//clear region for next frame
		regions[i]._enemys.clear();
		regions[i]._enemyBullets.clear();
		regions[i]._player.clear();
		regions[i]._playerBullets.clear();
	}
}