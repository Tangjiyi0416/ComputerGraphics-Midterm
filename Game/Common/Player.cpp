#include "Player.h"
#include "Boss0.h"
class Boss0;
Player* Player::_instance = nullptr;
Player::Player(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_exp{ 0 }, _totalExp{ 0 }, GameObject{
	parent, localPosition, localRotation, localScale
}
{
	_shapesNumber = 4;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, -0.6f, 0), vec3(), vec3(4.6f, 2.f, 1.f));
	_shapes[0]->SetColor(vec4(.5f, 0.7f, 0.2f, 1.0f));
	_shapes[1] = new Lens(vec3(0.f, 0.f, 0), vec3(0), vec3(5.f));
	_shapes[1]->SetColor(vec4(.8f, .8f, .8f, 1.0f));
	_shapes[2] = new Lens(vec3(2.f, -1.5f, 0), vec3(0));
	_shapes[2]->SetColor(vec4(1.0f, 1.f, 1.f, 1.0f));
	_shapes[3] = new Lens(vec3(-2.f, -1.5f, 0), vec3(0));
	_shapes[3]->SetColor(vec4(1.0f, 1.f, 1.f, 1.0f));

	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_shield = new Shield(10, this, vec3(), vec3(0, 0, 90), vec3(4.f));
	_children.pushBack(_shield);
	SecGun* _gun = new SecGun(Faction::Player, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f));
	_guns.pushBack(_gun);
	_children.pushBack(_gun);
	_collider = new Collider(this, ColliderType::Player, vec2(localPosition.x, localPosition.y), vec2(2, 5), vec2(localScale.x, localScale.y), std::bind(&Player::Onhit, this, std::placeholders::_1), 0b100);
	_uText = new Text("z: get more gun, x: +1 damage, c: +1 shield", vec3(1.f, 1.f, 0.3f), -SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 + 46, 0.5f);
}
Player::~Player()
{
	delete _collider;
	delete _uText;
	Player::_instance = nullptr;
}
void Player::Update(float dt) {
	//DEBUG SHIELD TEST
	if (InputUtilities::GetKeyState('1') && _counter >= 0.1f) {
		_shield->AddShield(1);
		_counter = 0;
	}
	if (InputUtilities::GetKeyState('2') && _counter >= 0.1f) {
		damage++;
		_counter = 0;
	}
	if (InputUtilities::GetKeyState('3') && _counter >= 0.1f) {
		_health = INT32_MAX;
		_counter = 0;
	}
	if (_canMissile) {
		if (_counter >= 0.3f) {
			_missileCounter++;
			_counter = 0;

		}
		if (InputUtilities::GetKeyState('f')) {
			while (_missileCounter > 0) {
				BulletManager::GetInstance()->SpawnMissile(Faction::Player, Boss0::GetInstance(), localPosition, vec3(0), vec3(1.2f), damage);
				_missileCounter--;
			}
		}

	}
	_counter += dt;
	if (_exp >= _threshold) {
		if (!_utextShow)
			TimedTextManager::SpawnText("Level up!", 1, vec3(1.f, 1.f, 0.3f), vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 + 96), 0.5f);
		_utextShow = true;

		if (InputUtilities::GetKeyState('z')) {
			if (_uCount == 2) {
				SecGun* _gun = new SecGun(Faction::Player, this, vec3(2.f, -1.5f, 0), vec3(), vec3(.5f));
				_guns.pushBack(_gun);
				_children.pushBack(_gun);
				_gun = new SecGun(Faction::Player, this, vec3(-2.f, -1.5f, 0), vec3(), vec3(.5f));
				_guns.pushBack(_gun);
				_children.pushBack(_gun);
			}
			else {
				SecGun* _gun = new SecGun(Faction::Player, this, vec3(0, 1.2071f - _guns.size(), 0), vec3(), vec3(.5f));
				_guns.pushBack(_gun);
				_children.pushBack(_gun);
			}
			_utextShow = false;

		}
		else if (InputUtilities::GetKeyState('x')) {
			damage++;
			_utextShow = false;
		}
		else if (InputUtilities::GetKeyState('c')) {
			_shield->AddShield(1);
			_utextShow = false;
		}
		if (!_utextShow) {
			_exp -= _threshold;
			_threshold += 10;
			_uCount++;
		}
	}

	//Handle movement
	vec3 _direction;

	if (InputUtilities::GetKeyState('d') || InputUtilities::GetKeyState('D'))_direction.x += 1;
	if (InputUtilities::GetKeyState('a') || InputUtilities::GetKeyState('A'))_direction.x -= 1;
	if (InputUtilities::GetKeyState('w') || InputUtilities::GetKeyState('W'))_direction.y += 1;
	if (InputUtilities::GetKeyState('s') || InputUtilities::GetKeyState('S'))_direction.y -= 1;
	_direction *= dt * _speed;
	localPosition += _direction;
	UpdateTRSMatrix();
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->setModelMatrix(_trs);
	}
	_collider->SetPosition(localPosition.x, localPosition.y);
	_collider->UpdateRegion();
	//SetPosition every child
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Update(dt);
		curChild = curChild->next();
	}

	if (InputUtilities::GetKeyState(' ')) {
		//ListNode<MainGun*>* curGun = _guns.front();
		//while (curGun != nullptr) {
		//	curGun->data->Shoot();;
		//	curGun = curGun->next();
		//}
		ListNode<SecGun*>* curGun2 = _guns.front();
		while (curGun2 != nullptr) {
			curGun2->data->Shoot();;
			curGun2 = curGun2->next();
		}

	}
}
void Player::Onhit(const Collider& other) {
	//std::cout << "Player was Hit" << std::endl;
}
void Player::TakeDamage(int damage) {
	if (_shield->GetShieldCount()) {
		_shield->AddShield(-1);
		return;
	}
	_health -= damage;
	//std::cout << _health << std::endl;
	if (_health <= 0) {
		_disabled = true;
	}
}
void Player::Draw() {
	for (size_t i = 0; i < _shapesNumber; i++)
	{
		_shapes[i]->Draw();
	}
	ListNode<GameObject*>* curChild = _children.front();
	while (curChild != nullptr) {
		curChild->data->Draw();
		curChild = curChild->next();
	}
}