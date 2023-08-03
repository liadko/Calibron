#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using v2f = sf::Vector2f;
using std::vector;
using std::cout;

struct Piece
{
    int w, h;

    Piece();
    Piece(int w, int h);
    bool operator==(const Piece& other) const;
};

//typedef sf::Vector2i Coord;

struct Placement
{
    int pieceIndex;
    //Piece pieceSize;
    //bool rotated;
    //Coord position;

    int data; // holds position and size in binary, x, y, w, h each one byte
    
    //Placement();
    //Placement(int pieceIndex, Coord pos);
    Placement(int x, int y); //single tile constuctor
    bool operator==(const Placement& other) const;
    int getW() const, getH() const, getX() const, getY() const;
    void setX(int), setY(int);
    void setW(int), setH(int), setSize(int);
    void rotate();
};

struct State {
    std::vector<Placement> placements;
    int availablePieces;
    int lastPlacementData;
    std::vector<int> forbiddenPlacements; //it is forbidden because we tried it, and it didn't work
    
    State();
    void place(const Placement& placement);
    //int pieceCount();
    bool fits(const Placement& placement) const;
    void addLastPlacementToForbidden();
};


//Graphics
void initOutlineShape();
void drawGrid(sf::RenderWindow& window);
void drawPiece(sf::RenderWindow& window, const Placement& placement);
//void highlightTile(sf::RenderWindow& window, Coord coord);
//void saveScreenshot(const sf::RenderWindow& window, int index);
void draw(sf::RenderWindow& window);

//Algorithm
bool advance();
bool clash(const Placement& p1, const Placement& p2);
//State stateWith(State state, Placement placement);
bool backtrack();

//game
const int tileAmountW = 40, tileAmountH = 40;
const int pieceCount = 12;

//Pieces
extern Piece pieceSizes[pieceCount];


//Graphics
const int rectScalingFactor = 18;
const int width = tileAmountW * 21, height = tileAmountH * 21;
const int gridWidth = tileAmountW * rectScalingFactor;
const int gridHeight = tileAmountH * rectScalingFactor;

//Rectangle
extern sf::RectangleShape rect, edges;
extern v2f gridPos;


//Algorithm
extern State mainState;
extern std::vector<State> states;