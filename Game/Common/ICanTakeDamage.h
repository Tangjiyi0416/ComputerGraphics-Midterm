#pragma once
class ICanTakeDamage
{
public:
	virtual ~ICanTakeDamage() {};

	virtual void TakeDamage(int damage) = 0;
};
