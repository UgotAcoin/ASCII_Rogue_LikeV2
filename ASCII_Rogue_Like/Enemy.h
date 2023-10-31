#pragma once
class Enemy
{
public:
	Enemy();

	//initialise the enemy
	void initialise(int xPos, int yPos, int level, char type);

	//checkers
	bool isEnemyActive();
	bool checkIfDead();

	//damage
	void takeDamage(int damage);

	//getters
	int getXPosition();
	int getYPosition();
	int getHP();
	int getStrength();
	int getDefence();
	int getExp();
	int getGoldReward();
	char getType();

	//setters
	void dead();
	void setXPosition(int& newX);
	void setYPosition(int& newY);
	void setHP(int hp);
	void setInactive();

private:
	bool _active;
	char _type;
	int _xPos;
	int _yPos;
	int _HP;
	int _strength;
	int _defence;
	int _expReward;
	int _goldReward;
};