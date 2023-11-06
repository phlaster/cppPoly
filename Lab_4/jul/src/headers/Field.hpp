#pragma once
#include "Block.hpp"
#include <SFML/Graphics.hpp>

class Field {
protected:
	float width, height, offset;
	int blocksInRow, blocksInCol;
	int blockLife;
	sf::Color colorArray[4]{ sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue };

public:
	std::vector<sf::RectangleShape> blocks;
	std::vector<sf::CircleShape> bonusBalls;
	std::vector<int> blocksHealths;
	Field();
	int zeroLifeBlocks;
	std::vector<sf::CircleShape> lifes;
	~Field() {};
	void generateField(std::vector<sf::RectangleShape>& blocks);
	void generateLife();
	void delLife();
	float getWidth();
	float getHeight();
	int getBlockInRow();
	int getBlockInCol();
	int getHealthByColor(sf::RectangleShape& block);
	bool isHealthZero(sf::RectangleShape& block);
	void setBlockType(sf::Color& blockColor, int& blockHealth);
	void setBlockHealth(sf::RectangleShape& block, int life);
	int getBlockHealth() {
		return blockLife;
	}


};