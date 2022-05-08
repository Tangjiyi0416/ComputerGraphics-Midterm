#include "Player.h"
Player* Player::_instance = nullptr;
Player::Player(GameObject* parent, const vec3& localPosition, const vec3& localRotation, const vec3& localScale)
	:_exp{ 0 }, GameObject{
	parent, localPosition, localRotation, localScale
}
{
	_shapesNumber = 4;
	_shapes = new Shape * [_shapesNumber];
	//vec3 a = vec3(0,1.2071,0);
	_shapes[0] = new Triangle(vec3(0, -0.6f, 0), vec3(), vec3(4.6f, 2.f, 1.f));
	_shapes[0]->SetColor(vec4(.5f, 0.7f, 0.2f, 1.0f));
	_shapes[1] = new Lens(vec3(0.f, 0.f, 0), vec3(0), vec3(5.f));
	_shapes[1]->SetColor(vec4(1.0f, 1.f, 1.f, 1.0f));
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
	MainGun* _gun = new MainGun(Faction::Player, this, vec3(0, 1.2071f, 0), vec3(), vec3(.5f));
	_guns.pushBack(_gun);
	_children.pushBack(_gun);
	_collider = new Collider(this, ColliderType::Player, vec2(localPosition.x, localPosition.y), vec2(2, 5), vec2(localScale.x, localScale.y), std::bind(&Player::Onhit, this, std::placeholders::_1), 0b100);
}

Player::~Player()
{
	delete _collider;
	Player::_instance = nullptr;
}
void Player::Update(float dt) {
	//DEBUG SHIELD TEST
	if (InputUtilities::GetKeyState('1') && _counter >= 0.1f) {
		_shield->AddShield(1);
		_counter = 0;
	}
	_counter += dt;
	if (!_u1 && _exp >= 40) {
		TimedTextManager::SpawnText("z: 1 more gun, x: +1 damage, c: +1 shield", 10, vec3(1.f, 1.f, 0.3f), vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 + 48), 0.4f);
		if (InputUtilities::GetKeyState('z')) {
			MainGun* _gun = new MainGun(Faction::Player, this, vec3(0, 1.2071f - _guns.size(), 0), vec3(), vec3(.5f));
			_guns.pushBack(_gun);
			_children.pushBack(_gun);
			_u1 = true;
		}

		if (InputUtilities::GetKeyState('x')) {
			damage++;
			_u1 = true;
		}
		if (InputUtilities::GetKeyState('c')) {
			_shield->AddShield(1);
			_u1 = true;
		}
	}
	else if (!_u2 && _exp >= 60) {
		TimedTextManager::SpawnText("z: 1 more gun, x: +1 damage, c: +1 shield", 10, vec3(1.f, 1.f, 0.3f), vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 + 48), 0.4f);
		if (InputUtilities::GetKeyState('z')) {
			MainGun* _gun = new MainGun(Faction::Player, this, vec3(0, 1.2071f - _guns.size(), 0), vec3(), vec3(.5f));
			_guns.pushBack(_gun);
			_children.pushBack(_gun);
			_u2 = true;
		}

		if (InputUtilities::GetKeyState('x')) {
			damage++;
			_u2 = true;
		}
		if (InputUtilities::GetKeyState('c')) {
			_shield->AddShield(1);
			_u2 = true;
		}
	}
	else if (!_u3 && _exp >= 80) {
		TimedTextManager::SpawnText("z: 1 more gun, x: +1 damage, c: +1 shield", 10, vec3(1.f, 1.f, 0.3f), vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 + 48), 0.4f);
		if (InputUtilities::GetKeyState('z')) {
			MainGun* _gun = new MainGun(Faction::Player, this, vec3(0, 1.2071f - _guns.size(), 0), vec3(), vec3(.5f));
			_guns.pushBack(_gun);
			_children.pushBack(_gun);
			_u3 = true;
		}

		if (InputUtilities::GetKeyState('x')) {
			damage++;
			_u3 = true;
		}
		if (InputUtilities::GetKeyState('c')) {
			_shield->AddShield(1);
			_u3 = true;
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
		ListNode<MainGun*>* curGun = _guns.front();
		while (curGun != nullptr) {
			curGun->data->Shoot();;
			curGun = curGun->next();
		}

	}
}
void Player::Onhit(const Collider& other) {
	std::cout << "Player was Hit" << std::endl;
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