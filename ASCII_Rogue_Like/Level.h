#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Shop.h"

#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <conio.h>
#include <random>
#include <ctime>

using namespace std;

class Level
{
public:
	Level();

	//LevelBuilding
	void loadLevel(int level);
	void buildUi(string state[20]);
	void printUi();
	void startMenu();

	//Movement
	void play();
	void moveUp();
	void moveRight();
	void moveLeft();
	void moveDown();

	//interation 
	void nextStage();
	void treasure();

	//inventory
	void addItemToInventory(int itemId);
	void useItem(Item item);
	void openInventory();
	void emptyInventory();

	//enemy
	void initialiseEnemies();
	void enemiesRoam();
	void singleEnemyRoam(Enemy &enemy);
	void initiateCombat(Enemy &enemy);
	void fight(Enemy &enemy, string name);
	void setAllEnemiesInactive();

	//shop
	void startShop();
	void buyItem(Item item);

	//basic functions
	void clearScreen();
	void waitForKeypress();
	void clearLog();
	bool quitGame();
	void gameOverDisplay();


private:

	ifstream inStream;

	int currentLevel = 0;
	int fleeing = 0;
	string currentGameState[20];
	string gameLog[3];
	string UI[24];

	char input;
	bool gameOver = false;
	bool gameBeaten = false;
	bool quit = false;
	bool loopMenu = true;

	Player _player;
	Enemy _enemy;
	Shop _shop;
	vector<Item> inventory;

	Enemy enemy0;
	Enemy enemy1;
	Enemy enemy2;
	Enemy enemy3;
	Enemy enemy4;
	Enemy enemy5;
	Enemy enemy6;
	Enemy enemy7;
	Enemy enemy8;
	Enemy enemy9;

};

