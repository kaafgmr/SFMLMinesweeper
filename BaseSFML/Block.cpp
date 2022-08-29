#include "Block.hpp"
#include <iostream>

Block::Block(float x, float y, int s)
{
	posX       = x;
	posY       = y;
	size       = s;
	Neighbours = 0;
	IsOpen     = false;
	IsBomb     = false;
	IsMarked   = false;
	
	NormalBlock.setSize(sf::Vector2f((float)size, (float)size));
	NormalBlock.setPosition(sf::Vector2f(posX, posY));
	NormalBlock.setFillColor(sf::Color(127, 127, 127));

	OpenBlock = NormalBlock;
	OpenBlock.setFillColor(sf::Color(64, 64, 64));

	font.loadFromFile("Fonts/digital-7.ttf");

	int numberSize = size - 10;
	float pX = posX + size * 0.5f;
	float pY = posY + (size * 0.5f) - (size - numberSize);

	number.setFont(font);
	number.setCharacterSize(numberSize);
	number.setString(std::to_string(Neighbours));
	number.setOrigin(number.getLocalBounds().width * 0.5f, number.getLocalBounds().height * 0.5f);
	number.setPosition(sf::Vector2f(pX, pY));

	BombBlock = NormalBlock;
	BombBlock.setFillColor(sf::Color(255, 0, 42));
	bombTexture.loadFromFile("Images/bomb.png");
	bombSprite.setTexture(bombTexture);
	bombSprite.setPosition(sf::Vector2f(posX, posY));
	bombSprite.scale(sf::Vector2f(size * 0.11f, size * 0.11f));

	markedTexture.loadFromFile("Images/flag.png");
	markedSprite.setTexture(markedTexture);
	markedSprite.setPosition(sf::Vector2f(posX,posY));
	markedSprite.scale(sf::Vector2f(size * 0.11f, size * 0.11f));
}

bool Block::ClickedOnBlock(sf::RenderWindow& window)
{
	int mouseX          = sf::Mouse::getPosition(window).x;
	int mouseY          = sf::Mouse::getPosition(window).y;
	float leftPos       = posX;
	float rightPos      = posX + size;
	float topPos        = posY;
	float bottomPos     = posY + size;
	bool clickedOnBlock = false;

	if (mouseX > leftPos && mouseX < rightPos && mouseY > topPos && mouseY < bottomPos)
	{
		clickedOnBlock = true;
	}

	return clickedOnBlock;
}

float Block::getposX()
{
	return posX;
}

float Block::getPosY()
{
	return posY;
}

void Block::setToBomb()
{
	IsBomb = true;
}

bool Block::getIsBomb()
{
	return IsBomb;
}

void Block::Open()
{
	IsOpen = true;
}

bool Block::GetIsOpen()
{
	return IsOpen;
}

void Block::SetNeighbour(int amount)
{
	Neighbours = amount;
}

int Block::getNeighbours()
{
	return Neighbours;
}

void Block::Draw(sf::RenderWindow* window)
{
	window->draw(NormalBlock); //draw closed block
	if (IsOpen)
	{
		if (IsBomb)
		{
			window->draw(BombBlock);
			window->draw(bombSprite);
		}
		else// not a bomb
		{
			window->draw(OpenBlock);
			if (Neighbours > 0) //number block
			{
				number.setString(std::to_string(Neighbours));
				number.setOrigin(number.getLocalBounds().width * 0.5f, number.getLocalBounds().height * 0.5f);
				window->draw(number);
			}
		}
	}

	if (!IsOpen && IsMarked)
	{
		window->draw(markedSprite);
	}

}

void Block::Mark()
{
	IsMarked = IsMarked == true ? false : true;
}

Block::~Block()
{
}