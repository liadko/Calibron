#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "header.h"

using v2f = sf::Vector2f;

//
//Piece
//

Piece::Piece() : w(-1), h(-1) {}
Piece::Piece(int w, int h) : w(w), h(h) {}

bool Piece::operator==(const Piece& other) const
{
	return w == other.w && h == other.h;
}

//
//Placement
//

//Placement::Placement() : pieceIndex(0), data(0) {}
//Placement::Placement(int sizeIndex, Coord pos, bool rotated) {
//
//	pieceIndex = sizeIndex;
//
//	int w = pieceSizes[sizeIndex].w;
//	int h = pieceSizes[sizeIndex].h;
//	if (rotated)
//	{
//		int temp = w;
//		w = h;
//		h = temp;
//	}
//
//	data = w;
//	data |= h << 8;
//	data |= pos.x << 16;
//	data |= pos.y << 24;
//}
Placement::Placement(int x, int y) //tile constructor
	: data(1 | (1 << 8) | (x << 16) | (y << 24)), pieceIndex(-1) {}


bool Placement::operator==(const Placement& other) const
{
	return data == other.data;
}

int Placement::getW() const
{
	return data & 0xff;
}

int Placement::getH() const
{
	return (data >> 8) & 0xff;
}

int Placement::getX() const
{
	return (data >> 16) & 0xff;
}

int Placement::getY() const
{
	return (data >> 24) & 0xff;
}

void Placement::setSize(int sizeIndex) 
{
	pieceIndex = sizeIndex;
	data &= ~(0xffff);
	Piece size = pieceSizes[pieceIndex];
	data |= size.w | (size.h << 8);
}

void Placement::setW(int w)
{
	data &= ~0xff;
	data |= w;
}

void Placement::setH(int h)
{
	data &= ~(0xff << 8);
	data |= h << 8;
}

void Placement::setX(int x)
{
	data &= ~(0xff << 16);
	data |= x << 16;
}

void Placement::setY(int y)
{
	data &= ~(0xff << 24);
	data |= y << 24;
}

void Placement::rotate()
{
	int w = getW();
	setW(getH());
	setH(w); 
}


State::State() : availablePieces((1 << pieceCount) - 1), lastPlacementData(-1) {}

void State::place(const Placement& placement)
{
	lastPlacementData = placement.data;
	states.push_back(*this);
	placements.push_back(placement);
	availablePieces &= ~(1 << placement.pieceIndex); //take out of available pieces

}

//int State::pieceCount()
//{
//	int c = 0;
//	int pos = 1;
//	for (int i = 0; i < pieceCount; i++, pos <<= 1)
//		if ((availablePieces & pos) == 0)
//			c++;
//	return c;
//}



bool State::fits(const Placement& placement) const
{
	// check if piece falls off edge
	if (placement.getX() + placement.getW() > tileAmountW)
		return false;

	if (placement.getY() + placement.getH() > tileAmountH)
		return false;


	//also should check if the piece clashes with any other pieces on the board
	for (const Placement& other : placements)
		if (clash(placement, other))
			return false;


	return true;
}

void State::addLastPlacementToForbidden()
{
	auto indexOfBigger = std::lower_bound(forbiddenPlacements.begin(), forbiddenPlacements.end(), lastPlacementData);
	forbiddenPlacements.insert(indexOfBigger, lastPlacementData);
}