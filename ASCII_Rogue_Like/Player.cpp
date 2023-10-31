#include "Player.h"

Player::Player()
{

}

//player's basic stats
void Player::newGame()
{
	_level = 1;
	_currentHP = 100;
	_maxHP = 100;
	_strength = 5;
	_defense = 5;
	_exp = 0;
	_totalExpNeeded = 100;
	_gold = 0;
}

//checks player remaining hp
bool Player::isPlayerDead()
{
	if (_currentHP > 0) {
		return false;
	} else {
		return true;
	}
}

//setters
void Player::setLevel(int level)
{
	_level = level;
}
void Player::setHP(int hp)
{
	_currentHP = hp;
}
void Player::setMaxHP(int hp)
{
	_maxHP = hp;
}
void Player::setStrength(int str)
{
	_strength = str;
}
void Player::setDefence(int def)
{
	_defense = def;
}
void Player::setCurrentExp(int exp)
{
	_exp = exp;
}
void Player::setExpNeededToLevel(int exp)
{
	_totalExpNeeded = exp;
}
void Player::setGold(int gold)
{
	_gold = gold;
}

//getters
int Player::getLevel()
{
	return _level;
}
int Player::getStr()
{
	return _strength;
}
int Player::getDef()
{
	return _defense;
}
int Player::getCurrentHP()
{
	return _currentHP;
}
int Player::getMaxHP()
{
	return _maxHP;
}
int Player::getCurrentExp()
{
	return _exp;
}
int Player::getTotalExpNeededToLevel()
{
	return _totalExpNeeded;
}
int Player::getGold()
{
	return _gold;
}

//increases:decreases
void Player::takeDamage(int damage)
{
	_currentHP -= damage;
}
void Player::earnExp(int exp)
{
	_exp += exp;
}
void Player::earnGold(int gold)
{
	_gold += gold;
}
void Player::loseGold(int gold)
{
	_gold -= gold;
}
void Player::maxHpUp(int amount)
{
	_maxHP += amount;
	_currentHP += amount;
}
void Player::maxHpDown(int amount)
{
	_maxHP -= amount;
	if (_currentHP > _maxHP) {
		_currentHP = _maxHP;
	}
}
void Player::levelUp()
{
	if (_exp > _totalExpNeeded) {
		cout << "Your EXP has hit the cap!\n";
		_level++;
		cout << "You reached level " + to_string(_level) + "!\n";
		_strength += (1 + (_level - 1));
		_defense += (1 + (_level - 1));
		_currentHP += (20 + (3 * _level));
		_maxHP += (20 + (3 * _level));
		//sets the value for next level
		_exp -= _totalExpNeeded;
		_totalExpNeeded = (100 + (_level * 40));
	}
}
void Player::heal(int heal)
{
	_currentHP += heal;
	if (_currentHP > _maxHP) {
		_currentHP = _maxHP;
	}
}
void Player::loseHealth(int amount)
{
	_currentHP -= amount;
	if (_currentHP < 0) {
		_currentHP = 1;
	}
}
void Player::increaseStrength(int str)
{
	_strength += str;
}
void Player::decreaseStrength(int str)
{
	_strength -= str;
}
void Player::increaseDefence(int def)
{
	_defense += def;
}
void Player::decreaseDefence(int def)
{
	_defense -= def;
}
