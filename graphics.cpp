#include <SFML/Graphics.hpp>
#include <iostream>
#include <format>
#include "header.h"



sf::RectangleShape rect, outline;
v2f gridPos;

Piece pieceSizes[pieceCount] =
{
    {23, 8},
    {23, 7},
    {20, 10},
    {20, 5},
    {20, 4},
    {15, 13},
    {15, 13},
    {15, 10},
    {15, 10},
    {12, 10},
    {10, 3},
    {7, 5}
    //{20, 1}
};


//create the shape of the grid outline
void initOutlineShape()
{
    gridPos = v2f(width / 2 - gridWidth / 2, height / 2 - gridHeight / 2);
    outline.setSize(v2f(gridWidth, gridHeight));
    outline.setPosition(gridPos);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color(0x4D9432FF));
    outline.setOutlineThickness(5);
}

//draw grid lines
void drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape gridLine(v2f(2, gridHeight));
    gridLine.setFillColor(sf::Color(255, 255, 255, 60));

    //vertical
    for (int i = 1; i < tileAmountW; i++)
    {
        gridLine.setPosition(gridPos + v2f(rectScalingFactor * i - 1, 0));
        //std::cout << gridPos.x << " " << gridPos.y << "\n";
        window.draw(gridLine);
    }

    //horizontal
    gridLine.setSize(v2f(gridWidth, 2));
    for (int i = 1; i < tileAmountH; i++)
    {
        gridLine.setPosition(gridPos + v2f(0, rectScalingFactor * i - 1));

        window.draw(gridLine);
    }

}


void drawPiece(sf::RenderWindow& window, const Placement& placement)
{
    rect.setSize(v2f(
        placement.getW() * rectScalingFactor,
        placement.getH() * rectScalingFactor));
    rect.setPosition(
        gridPos.x + placement.getX() * rectScalingFactor,
        gridPos.y + placement.getY() * rectScalingFactor);

    //outline
    rect.setFillColor(sf::Color(255, 200, 160));
    window.draw(rect);

    //main rect
    rect.setSize(rect.getSize() - v2f(2, 2));
    rect.setFillColor(sf::Color(0x942E2BFF));
    if(placement.pieceIndex >= 12)
        rect.setFillColor(sf::Color(0x002040FF));
    window.draw(rect);
}

//void highlightTile(sf::RenderWindow& window, Coord coord)
//{
//    sf::RectangleShape tile(v2f(rectScalingFactor, rectScalingFactor));
//    tile.setPosition(gridPos + (v2f)(coord * rectScalingFactor));
//    tile.setFillColor(sf::Color(50, 255, 100));
//
//    window.draw(tile);
//
//}

//void saveScreenshot(const sf::RenderWindow& window, int number)
//{
//
//    sf::Texture screenshot;
//    screenshot.create(width, height);
//    screenshot.update(window);
//    std::string filename = "Screenshots/screenshot " + std::to_string(number) + ".png";
//    if (screenshot.copyToImage().saveToFile(filename))
//    {
//        std::cout << "Big Success In Screenshot\n";
//    }
//    
//}

//draw all pieces and the grid
void draw(sf::RenderWindow& window)
{
    window.clear();

    
    for (const Placement& placement : mainState.placements)
        drawPiece(window, placement);


    drawGrid(window);

    window.draw(outline);

    window.display();
}