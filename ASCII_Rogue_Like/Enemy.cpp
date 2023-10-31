#include <iostream>
#include <string>

#include "Enemy.h"

using namespace std;

Enemy::Enemy()
{
	_active = false;
}

void Enemy::initialise(int xPos, int yPos, int level, char type)
{
	_active = true;

	switch (type)
	{
	case 'S':
		//Enemy is of type slime
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 25 + (level * 9);
		_strength = 3 + (level * 4);
		_defence = 1 + level;
		_expReward = 25 + (level * 2);
		_goldReward = 12 + level;
		break;
	case 'G':
		//Enemy is of type Goblin
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 35 + (level * 9);
		_strength = 3 + (level * 4);
		_defence = 1 + level;
		_expReward = 35 + (level * 2);
		_goldReward = 20 + level;
		break;
	case 'C':
		//Enemy is of type Cyclops
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 40 + (level * 9);
		_strength = 2 + (level * 5);
		_defence = 1 + level;
		_expReward = 45 + (level * 3);
		_goldReward = 30 + (level * 2);
		break;
	case 'D':
		//Enemy is of type Dragon
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 80 + (level * 8);
		_strength = (level * 7);
		_defence = 5 + (level * 4);
		_expReward = 120 + (level * 3);
		_goldReward = 50 + (level * 3);
		break;
	case 'K':
		//Enemy is of type King
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 1000;
		_strength = 70;
		_defence = 45;
		_expReward = 500;
		_goldReward = 1000;
		break;
	default:
		cout << "Enemy DATA ERROR" << endl;
	}

}

bool Enemy::isEnemyActive()
{
	return _active;
}
bool Enemy::checkIfDead()
{
	if (_HP > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::takeDamage(int damage)
{
	_HP = _HP - damage;
}

int Enemy::getXPosition()
{
	return _xPos;
}
int Enemy::getYPosition()
{
	return _yPos;
}
int Enemy::getHP()
{
	return _HP;
}
int Enemy::getStrength()
{
	return _strength;
}
int Enemy::getDefence()
{
	return _defence;
}
int Enemy::getExp()
{
	return _expReward;
}
int Enemy::getGoldReward()
{
	return _goldReward;
}
char Enemy::getType()
{
	return _type;
}

void Enemy::dead()
{
	_active = false;
}
void Enemy::setXPosition(int& newX)
{
	_xPos = newX;
}
void Enemy::setYPosition(int& newY)
{
	_yPos = newY;
}
void Enemy::setHP(int hp)
{
	_HP = hp;
}
void Enemy::setInactive()
{
	_active = false;
}
