#include "Board.hpp"
#include <iostream>

Board::Board(int w, int h, int offset, int blockamount, int bombAmount)
{
    gameOver = false;
	width = w;
	height = h;
	BlockAmount = blockamount;
    BombAmount = bombAmount;
    spacing = offset;
    float sz = (width / BlockAmount) - spacing;
    blockSize = sz;
}

std::vector<std::vector<Block*>> Board::GenerateBoard()
{
    std::vector<std::vector<Block*>> board(BlockAmount, std::vector<Block*>(BlockAmount, new Block(0, 0, (int)blockSize)));
    for (int i = 0; i < (int)BlockAmount; i++)
    {
        for (int j = 0; j < (int)BlockAmount; j++)
        {
            float x = i * (blockSize + spacing) + spacing * 0.5f;
            float y = j * (blockSize + spacing) + spacing * 0.5f;
            board[i][j] = new Block(x, y, (int)blockSize);
        }
    }
    return board;
}

void Board::GenerateBombs(std::vector<std::vector<Block*>> grid, int NumOfbombs, int numOfblocks)
{
    std::srand(std::time(NULL));
    int i = 0;
    while (i < NumOfbombs)
    {
        int randomX = std::rand() % (int)numOfblocks;
        int randomY = std::rand() % (int)numOfblocks;

        if (!grid[randomX][randomY]->getIsBomb())
        {
            grid[randomX][randomY]->setToBomb();
            i++;
        }
    }
}

void Board::CountNeighbours(std::vector<std::vector<Block*>> grid, int NumOfBlocks)
{
    for (int i = 0; i < NumOfBlocks; i++)
    {
        for (int j = 0; j < NumOfBlocks; j++)
        {
            int NeighbourAmount = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x > -1 && i + x < NumOfBlocks && j + y > -1 && j + y < NumOfBlocks && grid[i + x][j + y]->getIsBomb())
                    {
                        NeighbourAmount++;
                    }
                }
            }
            grid[i][j]->SetNeighbour(NeighbourAmount);
        }
    }
}

void Board::floodFill(std::vector<std::vector<Block*>> grid, int i, int j,int NumOfBlocks ,sf::RenderWindow &window)
{
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (i + x > -1 && i + x < NumOfBlocks && j + y > -1 && j + y < NumOfBlocks)
            {
                if (!grid[i + x][j + y]->GetIsOpen())
                {
                    Reveal(grid,i+x, j+y,NumOfBlocks,window);
                }
            }
        }
    }
}

void Board::Reveal(std::vector<std::vector<Block*>> grid,int i, int j, int NumOfBlocks, sf::RenderWindow& window)
{
    grid[i][j]->Open();
    if (grid[i][j]->getNeighbours() == 0)
    {
        floodFill(grid, i, j, NumOfBlocks, window);
    }
}

void Board::Update(std::vector<std::vector<Block*>> grid, int NumOfBlocks, sf::RenderWindow &window, bool isLeft)
{
    if (!gameOver)
    {
        for (int i = 0; i < NumOfBlocks; i++)
        {
            for (int j = 0; j < NumOfBlocks; j++)
            {
                if (grid[i][j]->ClickedOnBlock(window) && isLeft)
                {
                    Reveal(grid,i,j,NumOfBlocks,window);
                    if (grid[i][j]->getIsBomb()) // gameOver
                    {
                        gameOver = true;
                        GameOver(grid, NumOfBlocks);
                    }
                }

                if (grid[i][j]->ClickedOnBlock(window) && !isLeft)
                {
                    grid[i][j]->Mark();
                }
            }
        }
    }
}

void Board::GameOver(std::vector<std::vector<Block*>> grid, int NumOfBlocks)
{
    for (int i = 0; i < NumOfBlocks; i++)
    {
        for (int j = 0; j < NumOfBlocks; j++)
        {
            grid[i][j]->Open();
        }
    }
}

void Board::Draw(std::vector<std::vector<Block*>> grid, int NumOfBlocks, sf::RenderWindow& window)
{
    for (int i = 0; i < NumOfBlocks; i++)
    {
        for (int j = 0; j < NumOfBlocks; j++)
        {
            grid[i][j]->Draw(&window);
        }
    }
}



Board::~Board()
{
}