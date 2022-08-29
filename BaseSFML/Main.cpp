#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"

bool lockedLeft = false;
bool clickedLeft(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !lockedLeft)
    {
        lockedLeft = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        lockedLeft = false;
    }
    return lockedLeft;
}

bool lockedRight = false;
bool clickedRight(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && !lockedRight)
    {
        lockedRight = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
    {
        lockedRight = false;
    }
    return lockedRight;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minimalist Minesweeper", sf::Style::Titlebar);

    int spacing = 2;
    int blockSize = 50 - spacing;
    int NumOfBlocks = window.getSize().x / blockSize;
    int numOfBombs = (int)((NumOfBlocks * NumOfBlocks) * 0.1f);
    int width = window.getSize().x;
    int height = window.getSize().y;

    //createBoard
    Board* board = new Board(width, height, spacing, NumOfBlocks,numOfBombs);
    std::vector<std::vector<Block*>> grid(NumOfBlocks, std::vector<Block*>(NumOfBlocks,new Block(0, 0, blockSize)));

    //set up board
    grid = board->GenerateBoard();

    //Generate bombs
    board->GenerateBombs(grid ,numOfBombs, NumOfBlocks);

    board->CountNeighbours(grid, NumOfBlocks);

    sf::Event event;
    while (window.isOpen())
    {
        sf::Clock time;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if (clickedLeft(event))
            {
                //update
                board->Update(grid, NumOfBlocks, window,true);
            }
            if (clickedRight(event))
            {
                board->Update(grid, NumOfBlocks, window, false);
            }

        }

        //draw
        window.clear(sf::Color::Black);

        board->Draw(grid, NumOfBlocks, window);

        window.display();

        float FPS = 1.0f / time.restart().asSeconds();
        //std::cout << "FPS: " << FPS << std::endl;
    }

    return 0;
}