#include "headers/Field.hpp"
#include "headers/Source.hpp"
#include <iostream>
#include "headers/Game.hpp"

#define CHANCE 4

Field::Field()
{

	generateField(blocks);
}

void Field::generateField(std::vector<sf::RectangleShape>& blocks)
{
	
	float posX = 0, posY = 0;

	sf::Color blockColor;
	
	for (auto i = 0; i < BLOCKS_IN_COL; i++)
		for (auto j = 0; j < BLOCKS_IN_ROW; j++) {
			
			bool isBonus = false;
			posX = BLOKS_DISTANCE_X * (j + 1) + (j * BLOCK_SIDE);
			posY = BLOCK_SIDE + i * (BLOKS_DISTANCE_Y+ BLOCK_SIDE);
			setBlockType(blockColor, blockLife);
			sf::RectangleShape shape;
			if (blockColor == sf::Color::Green) {
				zeroLifeBlocks ++;
				std::cout << "zero life block has position " << posX << " " << posY << std::endl;
			}
			shape.setSize(sf::Vector2f(BLOCK_SIDE, BLOCK_SIDE));
			shape.setFillColor(blockColor);
			shape.setPosition(posX, posY);
			shape.setOutlineThickness((BLOCK_SIDE) / -(BLOCK_SIDE - 10));
			shape.setOutlineColor(sf::Color::Black);
			Block newBlock(BLOCK_SIDE, BLOCK_SIDE, posX, posY, blockLife, blockColor, isBonus);
			blocks.push_back(shape);
			blocksHealths.push_back(blockLife);
		}
}


void Field::generateLife() {
	float radius = 20;
	for (auto i = 0; i < 3; i++) {
		sf::CircleShape life;
		life.setRadius(radius);
		life.setPosition(i * 3 * radius, radius * 0.25);
		life.setFillColor(sf::Color::White);
		lifes.push_back(life);
	}
}
void Field::delLife()
{
	lifes.pop_back();
}
float Field::getWidth()
{
	return width;
}

float Field::getHeight()
{
	return height;
}

int Field::getBlockInRow()
{
	return blocksInRow;
}

int Field::getBlockInCol()
{
	return blocksInCol;
}
int Field::getHealthByColor(sf::RectangleShape& block)
{
	
	int index = -1;
	for (size_t i = 0; i < blocks.size(); i++) {
		if (&block == &blocks[i]) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		std::cout << blocksHealths[index] << std::endl;
		return index;
		//return blocksHealths[index];
		
	}
	return -100;

}



bool Field::isHealthZero(sf::RectangleShape& block)
{
	int index = getHealthByColor(block);
	std::cout << "block get health " << blocksHealths[index] << std::endl;
	std::cout << "block get index " << index << std::endl;

	int health = blocksHealths[index];
	if (health < 0) {
	
		return false;
	}
	if (health > 1) {
		
		block.setFillColor(colorArray[health - 1]);
		blocksHealths[index] --;
		return false;
	}
	blocksHealths.erase(blocksHealths.begin() + index);
	return true;
}

void Field::setBlockType(sf::Color& blockColor, int& blockHealth)
{

	switch (rand() % CHANCE) {
	case 0:
		blockColor = colorArray[0];
		blockLife =-1;
		break;
	case 1:
		blockColor = colorArray[1];
		blockLife = 1;
		break;
	case 2:
		blockColor = colorArray[2];
		blockLife = 2;
		break;
	default:
		blockColor = colorArray[3];
		blockLife = 3;
	}
}





