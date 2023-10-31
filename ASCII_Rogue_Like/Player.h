#pragma once

#include <iostream>
#include <string>

using namespace std;

class Player
{

public:
	Player();

	//player's basic stats
	void newGame();

	//checks if player has hp remaining
	bool isPlayerDead();

	//setters
	void setLevel(int level);
	void setHP(int hp);
	void setMaxHP(int hp);
	void setStrength(int str);
	void setDefence(int def);
	void setCurrentExp(int exp);
	void setExpNeededToLevel(int exp);
	void setGold(int gold);

	//getters
	int getLevel();
	int getStr();
	int getDef();
	int getCurrentHP();
	int getMaxHP();
	int getCurrentExp();
	int getTotalExpNeededToLevel();
	int getGold();

	//increases:decreases
	void takeDamage(int damage);
	void earnExp(int exp);
	void earnGold(int gold);
	void loseGold(int gold);
	void maxHpUp(int amount);
	void maxHpDown(int amount);
	void levelUp();
	void heal(int heal);
	void loseHealth(int amount);
	void increaseStrength(int str);
	void decreaseStrength(int str);
	void increaseDefence(int def);
	void decreaseDefence(int def);

private:
	int _level;
	int _currentHP;
	int _maxHP;
	int _strength;
	int _defense;
	int _exp;
	int _totalExpNeeded;
	int _gold = 0;
};

