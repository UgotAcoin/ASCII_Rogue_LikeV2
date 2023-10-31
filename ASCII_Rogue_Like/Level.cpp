#include "Level.h"

Level::Level()
{

}

void Level::loadLevel(int level)
{
	string levelString = to_string(level);
	string file = "Level" + levelString + ".txt";
	currentLevel = level;

	inStream.open(file);
	if (inStream.fail()) {
		const char* fileCString = file.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	string line;
	for (int i = 0; i < 20; i++) {
		getline(inStream, line);
		currentGameState[i] = line;
	}

	inStream.close();
}
void Level::buildUi(string state[20])
{
	string line;

	for (int i = 0; i < 24; i++) {

		line = "";

		if (i < 20) {
			line += state[i];
		}
		
		if (i == 0) {
			int level = _player.getLevel();
			string sLevel = to_string(level);
			line += " Lvl: " + sLevel;
		}
		
		if (i == 1) {
			int strLev = _player.getStr();
			string sStrLev = to_string(strLev);
			line += " Str: " + sStrLev;
		}

		if (i == 2) {
			int defLev = _player.getDef();
			string sDefLev = to_string(defLev);
			line += " Def: " + sDefLev;
		}

		if (i == 3) {
			int gold = _player.getGold();
			line += " Gold: " + to_string(gold);
		}

		if (i == 4) {
			int items = inventory.size();
			line += " Items: " + to_string(items) + "/5";
		}

		if (i == 6) {
			line += " Health:";
		}

		if (i == 7) {
			int currHP = _player.getCurrentHP();
			int maxHP = _player.getMaxHP();
			string sCurrHP = to_string(currHP);
			string sMaxHP = to_string(maxHP);

			line += " " + sCurrHP + "/" + sMaxHP;
		}

		if (i == 9) {
			line += " EXP:";
		}

		if (i == 10) {
			int exp = _player.getCurrentExp();
			int totalExp = _player.getTotalExpNeededToLevel();
			string sExp = to_string(exp);
			string sTotalExp = to_string(totalExp);

			line += " " + sExp + "/" + sTotalExp;
		}

		if (i == 12) {
			line += " @ Player";
		}

		if (i == 13) {
			line += " T Treasure";
		}

		if (i == 14) {
			line += " H Ladder";
		}

		if (i == 15) {
			line += " S Slime";
		}

		if (i == 16) {
			line += " G Goblin";
		}

		if (i == 17) {
			line += " C Cycplos";
		}

		if (i == 18) {
			line += " D Dragon";
		}

		if (i == 19) {
			line += " K King";
		}

		if (i == 21) {
			line += gameLog[0];
		}

		if (i == 22) {
			line += gameLog[1];
		}

		if (i == 23) {
			line += gameLog[2];
		}

		UI[i] = line += "\n";
	}
}
void Level::printUi()
{
	clearScreen();

	for (int i = 0; i < 24; i++) {
		cout << UI[i];
	}
}
void Level::startMenu()
{
	bool isDone = false;
	clearScreen();

	cout << "Welcome to Dragon Castle, an ASCII adventure game" << endl;
	cout << "Be sure to maximise the console window before you start to make\nsure you can see the whole interface.\n" << endl;
	while (isDone != true) {

		while (loopMenu)
		{
			cout << "Select an Option:" << endl;
			cout << "1 - New Game" << endl;
			cout << "2 - Quit" << endl;

			input = _getch();

			if (input != '1' && input != '2')
			{
				cout << "Invalid input, please try again.\n\n";
			}
			else
			{
				clearScreen();
				loopMenu = false;
			}
		}

		loopMenu = true;

		switch (input)
		{
		case '1':
			//New Game
			gameOver = false;
			gameBeaten = false;
			loadLevel(1);
			_player.newGame();
			emptyInventory();
			addItemToInventory(0);
			addItemToInventory(0);
			initialiseEnemies();
			buildUi(currentGameState);
			printUi();
			play();
			break;
		case '2':
			//Quit
			cout << "Goodbye!\n";
			quit = true;
			break;
		}

		if (quit)
		{
			return;
		}
	}

}

void Level::play()
{
	bool quit = false;

	while (!quit)
	{
		clearLog();

		input = _getch();

		if (input == 'w' || input == 'W')
		{
			moveUp();
			enemiesRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'a' || input == 'A')
		{
			moveLeft();
			enemiesRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 's' || input == 'S')
		{
			moveDown();
			enemiesRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'd' || input == 'D')
		{
			moveRight();
			enemiesRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'i' || input == 'I')
		{
			openInventory();
		}
		else if (input == 'q' || input == 'Q')
		{
			quit = quitGame();

			if (quit)
			{
				clearScreen();
				clearLog();
			}
			else
			{
				clearScreen();
			}
		}
		else
		{
			gameLog[0] = "Invalid input, try again.";
		}

		if (gameOver)
		{
			clearScreen();
			gameOverDisplay();
			quit = true;
		}

		if (!quit)
		{
			if (fleeing > 0)
			{
				gameLog[2] = "You are fleeing! (" + to_string(fleeing) + " more steps)";
			}
			buildUi(currentGameState);
			printUi();
		}
	}
}
void Level::moveUp()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine - 1].at(currentColumn);
	if (destination == '.')
	{
		currentGameState[currentLine - 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	} else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	} else if (destination == 'T')
	{
		currentGameState[currentLine - 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	} else if (destination == 'H')
	{
		nextStage();
	} else if (destination == 'M')
	{
		startShop();
	}

}
void Level::moveRight()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine].at(currentColumn + 1);
	if (destination == '.')
	{
		currentGameState[currentLine].replace(currentColumn + 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	} else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	} else if (destination == 'T')
	{
		currentGameState[currentLine].replace(currentColumn + 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	} else if (destination == 'H')
	{
		nextStage();
	} else if (destination == 'M')
	{
		startShop();
	}
}
void Level::moveLeft()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine].at(currentColumn - 1);
	if (destination == '.')
	{
		currentGameState[currentLine].replace(currentColumn - 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	} else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	} else if (destination == 'T')
	{
		currentGameState[currentLine].replace(currentColumn - 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	} else if (destination == 'H')
	{
		nextStage();
	} else if (destination == 'M')
	{
		startShop();
	}
}
void Level::moveDown()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine + 1].at(currentColumn);
	if (destination == '.')
	{
		currentGameState[currentLine + 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	} else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	} else if (destination == 'T')
	{
		currentGameState[currentLine + 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	} else if (destination == 'H')
	{
		nextStage();
	} else if (destination == 'M')
	{
		startShop();
	}
}

void Level::nextStage()
{
	if (currentLevel == 10)
	{
		//Game completed
		gameBeaten = true;
		gameOver = true;
		gameOverDisplay();
		waitForKeypress();
		clearScreen();

	}
	else
	{
		clearScreen();
		setAllEnemiesInactive();
		currentLevel++;
		cout << "You ascend the ladder to the next floor of the castle." << endl;
		cout << "\nPress any key to begin exploring floor number " + to_string(currentLevel) + "." << endl;
		waitForKeypress();
		loadLevel(currentLevel);
		initialiseEnemies();
		clearScreen();
	}
}
void Level::treasure()
{
	static default_random_engine rng(time(NULL));
	uniform_int_distribution<int> treasureRoll(0, 10);

	//This value needs to be updated as new items are added to ensure ill items are randomly obtainable.
	int roll = treasureRoll(rng);
	Item loot(roll);

	//Interface
	clearScreen();
	cout << "--------------------" << endl;
	cout << "|  Treasure Chest  |" << endl;
	cout << "--------------------" << endl;
	cout << "\nYou open the treasure chest..." << endl;
	cout << "\nAnd find a " + loot.getName() + "!" << endl;
	cout << "\nEffect: " + loot.getDescription() << endl;

	if (inventory.size() < 5)
	{
		cout << "\nYou put the " + loot.getName() + " into your inventory." << endl;
		addItemToInventory(roll);
	}
	else
	{
		cout << "\nYour inventory is full, use this item now? (Y/N)" << endl;
		bool decided = false;

		while (decided == false)
		{
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				cout << "You used the " + loot.getName() << endl;
				useItem(loot);
				decided = true;
			}
			else if (input == 'n' || input == 'N')
			{
				cout << "You discarded the " + loot.getName() + "..." << endl;
				decided = true;
			}
		}

	}

	cout << "\n\nPress any key to continue." << endl;
	waitForKeypress();
	buildUi(currentGameState);
	printUi();
}

void Level::addItemToInventory(int itemId)
{
	if (inventory.size() < 5)
	{
		Item item(itemId);
		inventory.push_back(item);
	}
}
void Level::useItem(Item item)
{
	int healAmount = item.getHealAmount();
	int healthLossAmount = item.getHealthLossAmount();
	int strengthUp = item.getStrUp();
	int strengthDown = item.getStrDown();
	int defenceUp = item.getDefUp();
	int defenceDown = item.getDefDown();
	int maxHpUp = item.getMaxHpUp();
	int maxHpDown = item.getMaxHpDown();
	
	_player.heal(healAmount);
	_player.loseHealth(healthLossAmount);
	_player.increaseStrength(strengthUp);
	_player.decreaseStrength(strengthDown);
	_player.increaseDefence(defenceUp);
	_player.decreaseDefence(defenceDown);
	_player.maxHpUp(maxHpUp);
	_player.maxHpDown(maxHpDown);
}
void Level::openInventory()
{
	if (inventory.size() == 0)
	{
		clearScreen();
		cout << "There are no items in your Inventory..." << endl;
		waitForKeypress();
	}
	else
	{
		bool closeInventory = false;
		while (closeInventory == false)
		{
			clearScreen();
			cout << "-----------------" << endl;
			cout << "|   INVENTORY   |" << endl;
			cout << "-----------------" << endl << endl;
			for (int x = 0; x < inventory.size(); x++)
			{
				int itemNumber = x + 1;
				cout << to_string(itemNumber) + " - " + inventory[x].getName() << endl;
			}

			cout << "\nType the corresponding number to inspect the item or press I again to exit your inventory." << endl;

			input = _getch();

			if (input == 'I' || input == 'i')
			{
				//Close inventory
				closeInventory = true;
			}

			if (input == '1' && inventory.size() > 0)
			{
				clearScreen();
				cout << inventory[0].getName() << endl;
				cout << "\n" + inventory[0].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[0]);
					inventory.erase(inventory.begin());
					closeInventory = true;
				}
			}

			if (input == '2' && inventory.size() > 1)
			{
				clearScreen();
				cout << inventory[1].getName() << endl;
				cout << "\n" + inventory[1].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[1]);
					inventory.erase(inventory.begin() + 1);
					closeInventory = true;
				}
			}

			if (input == '3' && inventory.size() > 2)
			{
				clearScreen();
				cout << inventory[2].getName() << endl;
				cout << "\n" + inventory[2].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[2]);
					inventory.erase(inventory.begin() + 2);
					closeInventory = true;
				}
			}

			if (input == '4' && inventory.size() > 3)
			{
				clearScreen();
				cout << inventory[3].getName() << endl;
				cout << "\n" + inventory[3].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[3]);
					inventory.erase(inventory.begin() + 3);
					closeInventory = true;
				}
			}

			if (input == '5' && inventory.size() > 4)
			{
				clearScreen();
				cout << inventory[4].getName() << endl;
				cout << "\n" + inventory[4].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[4]);
					inventory.erase(inventory.begin() + 4);
					closeInventory = true;
				}
			}
		}
	}
}
void Level::emptyInventory()
{
	inventory.clear();
}

void Level::initialiseEnemies()
{
	string file = "Level" + to_string(currentLevel) + "EnemyData.txt";
	inStream.open(file);
	if (inStream.fail())
	{
		//Convert to C-String to comply with perror function parameters.
		const char* fileCString = file.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	//First line of the EnemyData file is the number of Enemys on this level
	string sAmount;
	int amount;
	getline(inStream, sAmount);
	amount = stoi(sAmount, nullptr, 10);

	for (int x = 0; x < amount; x++)
	{
		//Read 3 lines of Enemy data from the file.
		string s_type;
		string s_xPos;
		string s_yPos;
		getline(inStream, s_type);
		getline(inStream, s_xPos);
		getline(inStream, s_yPos);

		//Process strings into suitable parameter types.
		int xPos;
		int yPos;
		xPos = stoi(s_xPos);
		yPos = stoi(s_yPos);
		char type = s_type[0];

		switch (x)
		{
		case 0:
			enemy0.initialise(xPos, yPos, currentLevel, type);
			break;
		case 1:
			enemy1.initialise(xPos, yPos, currentLevel, type);
			break;
		case 2:
			enemy2.initialise(xPos, yPos, currentLevel, type);
			break;
		case 3:
			enemy3.initialise(xPos, yPos, currentLevel, type);
			break;
		case 4:
			enemy4.initialise(xPos, yPos, currentLevel, type);
			break;
		case 5:
			enemy5.initialise(xPos, yPos, currentLevel, type);
			break;
		case 6:
			enemy6.initialise(xPos, yPos, currentLevel, type);
			break;
		case 7:
			enemy7.initialise(xPos, yPos, currentLevel, type);
			break;
		case 8:
			enemy8.initialise(xPos, yPos, currentLevel, type);
			break;
		case 9:
			enemy9.initialise(xPos, yPos, currentLevel, type);
			break;
		}

	}

	inStream.close();

}
void Level::enemiesRoam()
{
	singleEnemyRoam(enemy0);
	singleEnemyRoam(enemy1);
	singleEnemyRoam(enemy2);
	singleEnemyRoam(enemy3);
	singleEnemyRoam(enemy4);
	singleEnemyRoam(enemy5);
	singleEnemyRoam(enemy6);
	singleEnemyRoam(enemy7);
	singleEnemyRoam(enemy8);
	singleEnemyRoam(enemy9);
}
void Level::singleEnemyRoam(Enemy &enemy)
{
	static default_random_engine rng(time(NULL));
	uniform_int_distribution<int> randomDirection(1, 4);

	//Ensure that the Enemy is active in the current level.
	if (enemy.isEnemyActive() == true)
	{
		bool successfulMovement = false;

		int direction = randomDirection(rng);

		//variable initialisation outside of switch/case statement to avoid multiple initialization errors.
		int currentX = enemy.getXPosition();
		int currentY = enemy.getYPosition();
		int newX;
		int newY;
		char type;
		char valueAtCoordinates;
		string line;
		string destinationLine;
		string s_Type;

		switch (direction)
		{
		case 1:
			//Enemy moves UP

			//Verify that the Enemy is in fact at these coordinates.
			type = enemy.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX;
				newY = currentY - 1;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this Enemy to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Enemy object to reflect changes to the game state.
					enemy.setXPosition(newX);
					enemy.setYPosition(newY);
				}
			}
			break;
		case 2:
			//Enemy moves RIGHT
			//Verify that the Enemy is in fact at these coordinates.
			type = enemy.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX + 1;
				newY = currentY;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this Enemy to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Enemy object to reflect changes to the game state.
					enemy.setXPosition(newX);
					enemy.setYPosition(newY);
				}
			}
			break;
		case 3:
			//Enemy moves DOWN
			//Verify that the Enemy is in fact at these coordinates.
			type = enemy.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX;
				newY = currentY + 1;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this Enemy to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Enemy object to reflect changes to the game state.
					enemy.setXPosition(newX);
					enemy.setYPosition(newY);
				}
			}
			break;
		case 4:
			//Enemy moves LEFT
			//Verify that the Enemy is in fact at these coordinates.
			type = enemy.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX - 1;
				newY = currentY;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this Enemy to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Enemy object to reflect changes to the game state.
					enemy.setXPosition(newX);
					enemy.setYPosition(newY);
				}
			}
			break;
		}

		if (fleeing == 0)
		{
			initiateCombat(enemy);
		}
	}
}
void Level::initiateCombat(Enemy &enemy)
{
	//Check if the Enemy has landed in a square adjacent to the player
	int xPos = enemy.getXPosition();
	int yPos = enemy.getYPosition();
	string lineAbove = currentGameState[(yPos - 1)];
	string lineMiddle = currentGameState[yPos];
	string lineBelow = currentGameState[(yPos + 1)];
	if (lineAbove[(xPos - 1)] == '@' ||
		lineAbove[xPos] == '@' ||
		lineAbove[(xPos + 1)] == '@' ||
		lineMiddle[(xPos - 1)] == '@' ||
		lineMiddle[(xPos + 1)] == '@' ||
		lineBelow[(xPos - 1)] == '@' ||
		lineBelow[xPos] == '@' ||
		lineBelow[(xPos + 1)] == '@')
	{
		//Enemy found next to player, start fight.
		char type = enemy.getType();
		string enemyName;
		switch (type)
		{
		case 'S':
			gameLog[0] = "You have encountered a slime!";
			gameLog[1] = "Prepare for battle! Press any key...";
			enemyName = "Slime";
			buildUi(currentGameState);
			printUi();
			waitForKeypress();
			clearLog();
			break;
		case 'G':
			gameLog[0] = "You have encountered a goblin!";
			gameLog[1] = "Prepare for battle! Press any key...";
			enemyName = "Goblin";
			buildUi(currentGameState);
			printUi();
			waitForKeypress();
			clearLog();
			break;
		case 'O':
			gameLog[0] = "You have encountered an Ogre!";
			gameLog[1] = "Prepare for battle! Press any key...";
			enemyName = "Ogre";
			buildUi(currentGameState);
			printUi();
			waitForKeypress();
			clearLog();
			break;
		case 'D':
			gameLog[0] = "A fearsome Dragon blocks your path!";
			gameLog[1] = "Prepare for battle! Press any key...";
			enemyName = "Dragon";
			buildUi(currentGameState);
			printUi();
			waitForKeypress();
			clearLog();
			break;
		case 'K':
			gameLog[0] = "You stand before the Dragon King.";
			gameLog[1] = "Prepare for the final battle! Press any key...";
			enemyName = "Dragon King";
			buildUi(currentGameState);
			printUi();
			waitForKeypress();
			clearLog();
			break;
		}

		fight(enemy, enemyName);
	}
}
void Level::fight(Enemy &enemy, string name)
{
	static default_random_engine rng(time(NULL));
	uniform_int_distribution<int> damageVariation(3, 7);
	uniform_int_distribution<int> criticalHitRoll(1, 100);

	clearScreen();
	bool battleComplete = false;
	bool validAction = false;
	bool alive = true;
	cout << "You have engaged a Level " + to_string(currentLevel) + " " + name + "." << endl << endl;
	while (battleComplete == false)
	{
		cout << "You have " + to_string(_player.getCurrentHP()) + "/" + to_string(_player.getMaxHP()) + " HP" << endl;
		cout << "The " + name + " has " + to_string(enemy.getHP()) + " HP." << endl;
		validAction = false;
		while (validAction == false)
		{
			cout << "\nSelect action:" << endl;
			cout << "1 - Attack" << endl;
			cout << "2 - Inventory" << endl;
			cout << "3 - Flee" << endl;

			input = _getch();

			if (input == '1')
			{
				int baseDamage = _player.getStr();
				int bonusDamage = damageVariation(rng);
				int totalDamage = baseDamage + bonusDamage;
				int critRoll = criticalHitRoll(rng);
				clearScreen();
				cout << "You attack the " + name + "." << endl;
				if (critRoll > 90)
				{
					cout << "Critical hit!" << endl;
					totalDamage = totalDamage * 1.5;
				}
				totalDamage -= enemy.getDefence();
				if (totalDamage < 1)
				{
					totalDamage = 1;
				}
				cout << "You inflict " + to_string(totalDamage) + " damage." << endl << endl;
				enemy.takeDamage(totalDamage);
				alive = enemy.checkIfDead();
				if (alive == false)
				{
					//Enemy defeated
					cout << "You defeated the " + name + "!" << endl;
					cout << "You earned " + to_string(enemy.getExp()) + " Experience points. " << endl;
					cout << "You found " + to_string(enemy.getGoldReward()) + " gold on the " + name + "s corpse." << endl;
					cout << "Press any key to continue." << endl;
					_player.earnExp(enemy.getExp());
					_player.earnGold(enemy.getGoldReward());
					_player.levelUp();
					waitForKeypress();
					enemy.dead();

					//Remove the enemies symbol from the game state
					int xPos = enemy.getXPosition();
					int yPos = enemy.getYPosition();
					string line = currentGameState[yPos];
					line[xPos] = '.';
					currentGameState[yPos] = line;

					battleComplete = true;
				}
				else
				{
					//Enemies turn to attack
					int baseDamage = enemy.getStrength();
					int bonusDamage = damageVariation(rng);
					int totalDamage = baseDamage + bonusDamage;
					int critRoll = criticalHitRoll(rng);
					cout << "The " + name + " attacks you." << endl;
					if (critRoll > 90)
					{
						cout << "Ouch, you took Critical hit!" << endl;
						totalDamage = totalDamage * 1.5;
					}
					totalDamage -= _player.getDef();
					if (totalDamage < 1)
					{
						totalDamage = 1;
					}
					cout << "You take " + to_string(totalDamage) + " damage." << endl << endl;
					_player.takeDamage(totalDamage);
					if (_player.isPlayerDead())
					{
						cout << "\nYou have been defeated..." << endl;
						waitForKeypress();
						gameOver = true;
						battleComplete = true;
					}
				}
				validAction = true;
			}
			else if (input == '2')
			{
				clearScreen();
				openInventory();
				clearScreen();
				validAction = true;
			}
			else if (input == '3')
			{
				int fleeDamage = enemy.getStrength() + 10;
				cout << "\nYou fight off the " + name + " long enough to make your escape,\nbut you took " + to_string(fleeDamage) + " damage in the process." << endl;
				_player.takeDamage(fleeDamage);
				if (_player.isPlayerDead())
				{
					cout << "\nYou have been defeated..." << endl;
					waitForKeypress();
					gameOver = true;
				}
				else
				{
					fleeing = 3;
				}
				cout << "Press any key." << endl;
				waitForKeypress();
				battleComplete = true;
				validAction = true;
			}
			else
			{
				cout << "Invalid selection, try again." << endl;
			}
		}
	}

	battleComplete = true;
	clearScreen();
}
void Level::setAllEnemiesInactive()
{
	enemy0.setInactive();
	enemy1.setInactive();
	enemy2.setInactive();
	enemy3.setInactive();
	enemy4.setInactive();
	enemy5.setInactive();
	enemy6.setInactive();
	enemy7.setInactive();
	enemy8.setInactive();
	enemy9.setInactive();
}


void Level::startShop()
{
	clearScreen();
	bool done = false;
	Item i(0);
	cout << "------------------" << endl;
	cout << "|    MERCHANT    |" << endl;
	cout << "------------------" << endl << endl;
	_shop.prepareStock(currentLevel);
	while (!done)
	{
		_shop.displayItemsForSale();
		cout << endl << endl << "You have " + to_string(_player.getGold()) + " gold." << endl;
		cout << "\nChoose an item or press X to return to the map." << endl << endl;
		input = _getch();

		if (input == '1' && _shop.getStockSize() > 0)
		{
			i = _shop.getItem(1);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '2' && _shop.getStockSize() > 1)
		{
			i = _shop.getItem(2);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '3' && _shop.getStockSize() > 2)
		{
			i = _shop.getItem(3);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '4' && _shop.getStockSize() > 3)
		{
			i = _shop.getItem(4);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '5' && _shop.getStockSize() > 4)
		{
			i = _shop.getItem(5);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '6' && _shop.getStockSize() > 5)
		{
			i = _shop.getItem(6);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '7' && _shop.getStockSize() > 6)
		{
			i = _shop.getItem(7);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '8' && _shop.getStockSize() > 7)
		{
			i = _shop.getItem(8);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '9' && _shop.getStockSize() > 8)
		{
			i = _shop.getItem(9);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == 'x' || input == 'X')
		{
			done = true;
		}
	}
}
void Level::buyItem(Item item)
{
	if (inventory.size() >= 5)
	{
		cout << "Your backpack is too full for any more items..." << endl;
	}
	else if (_player.getGold() > item.getPrice())
	{
		_player.loseGold(item.getPrice());
		inventory.push_back(item);
		cout << "You purchase the " + item.getName() + "..." << endl;
	}
	else
	{
		cout << "You cannot afford the " + item.getName() + "..." << endl;
	}

	cout << "Press any key to continue." << endl;
	waitForKeypress();
	clearScreen();
}

void Level::clearScreen()
{
	cout << string(50, '\n');
}
void Level::waitForKeypress()
{
	_getch();
}
void Level::clearLog()
{
	for (int i = 0; i < 3; i++) {
		gameLog[i] = "";
	}
}
bool Level::quitGame()
{
	clearScreen();
	cout << "Are you sure you want to quit? (Y/N) \n";

	input = _getch();

	if (input == 'y' || input == 'Y')
	{
		clearScreen();
		return true;
	}
	else
	{
		return false;
	}
}
void Level::gameOverDisplay()
{
	if (gameBeaten)
	{
		clearScreen();
		cout << "                                CONGRATULATIONS!" << endl;
		cout << "                               You beat the game!\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	}
	else
	{
		cout << "                                   GAME OVER\n\n\n\n\n\n\n\n\n\n\n\nPress any key..." << endl;
		waitForKeypress();
		clearScreen();
	}
}
