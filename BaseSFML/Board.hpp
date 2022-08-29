#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <vector>
#include "Block.hpp"

class Board
{
	public:
		Board(int w, int h, int offset,int blockamount, int bombAmount);
		std::vector<std::vector<Block*>> GenerateBoard();
		void GenerateBombs(std::vector<std::vector<Block*>> grid,int NumOfbombs, int numOfblocks);
		void CountNeighbours(std::vector<std::vector<Block*>> grid, int NumOfBlocks);
		void Restart(std::vector<std::vector<Block*>> grid, int NumOfbombs, int numOfblocks);
		void floodFill(std::vector<std::vector<Block*>> grid, int i, int j, int NumOfBlocks, sf::RenderWindow& window);
		void Reveal(std::vector<std::vector<Block*>> grid, int i, int j, int NumOfBlocks, sf::RenderWindow& window);
		void Update(std::vector<std::vector<Block*>> grid, int NumOfBlocks, sf::RenderWindow& window, bool isLeft);
		void GameOver(std::vector<std::vector<Block*>> grid, int NumOfBlocks);
		void Draw(std::vector<std::vector<Block*>> grid, int NumOfBlocks, sf::RenderWindow& window);
		~Board();

	private:
		bool gameOver;
		float blockSize;
		int width;
		int height;
		int BlockAmount;
		int BombAmount;
		int spacing;
};

#endif