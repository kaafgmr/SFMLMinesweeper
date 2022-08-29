#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__
#include "SFML/Graphics.hpp"

class Block
{
	public:
		Block(float x, float y, int s);
		bool  ClickedOnBlock(sf::RenderWindow& window);
		float getposX();
		float getPosY();
		void  setToBomb();
		bool  getIsBomb();
		void  Open();
		bool  GetIsOpen();
		void  SetNeighbour(int amount);
		int   getNeighbours();
		void  Draw(sf::RenderWindow* window);
		void  Mark();
		~Block();

	private:
		float posX;
		float posY;
		int   size;
		int   Neighbours;
		bool  IsOpen;
		bool  IsBomb;
		bool  IsMarked;
		sf::RectangleShape NormalBlock;
		sf::RectangleShape OpenBlock;
		sf::RectangleShape BombBlock;
		sf::Texture bombTexture;
		sf::Sprite bombSprite;
		sf::Texture markedTexture;
		sf::Sprite markedSprite;
		sf::Font font;
		sf::Text number;
};

#endif