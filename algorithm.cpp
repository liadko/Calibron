
#include "header.h"


State mainState;
std::vector<State> states;


// place something on the board
// returns true if the board is solved
bool advance()
{

	if (mainState.availablePieces == 0)
	{
		//std::cout << "Solved.\n";
		return true;
	}


	//find the first empty tile
	bool found = false;
	Placement tile(0, 0);
	int x, y;
	for (y = 0; y < tileAmountH && !found; y++)
	{
		tile.setY(y);
		for (x = 0; x < tileAmountW && !found; x++)
		{
			tile.setX(x);
			if (mainState.fits(tile))
				found = true;
		}
	}

	x--; y--;

	//try to place a piece in the tile that was found

	const auto& forbiddens = mainState.forbiddenPlacements;

	Placement placement(x, y);

	int pos = 1;
	for (int pieceIndex = 0; pieceIndex < pieceCount; pieceIndex++, pos <<= 1)
	{
		if ((mainState.availablePieces & pos) == 0)
			continue;

		placement.setSize(pieceIndex);

		for (int rotation = 0; rotation < 2; rotation++)
		{
			if (rotation)
				placement.rotate();
			 
			if (!mainState.fits(placement))
				continue;

			if (std::binary_search(forbiddens.begin(), forbiddens.end(), placement.data))
				continue;

			mainState.place(placement);
			return false;
		}
	}

	//stuck
	//couldn't place any piece in the tile, current state is invalid
	return backtrack();

}

//revert to last guess, and remember to guess differently next time.
bool backtrack()
{
	//std::cout << "Backtracking\n";

	if (states.size() == 0) {
		std::cout << "Tried To backtrack but no states to backtrack to.\n";
		return false;
	}

	//pop last state
	mainState = states.back();
	states.pop_back();

	//remember not to enter it next time
	mainState.addLastPlacementToForbidden();

	return advance();
}


// code stolen from ChatGPT
bool clash(const Placement& p1, const Placement& p2)
{
	sf::Vector2i p1pos(p1.getX(), p1.getY());
	sf::Vector2i p2pos(p2.getX(), p2.getY());

	int p1Right = p1pos.x + p1.getW();
	int p1Bottom = p1pos.y + p1.getH();
	int p2Right = p2pos.x + p2.getW();
	int p2Bottom = p2pos.y + p2.getH();

	if (p1pos.x >= p2Right || p2pos.x >= p1Right) {
		return false; // No horizontal overlap
	}

	if (p1pos.y >= p2Bottom || p2pos.y >= p1Bottom) {
		return false; // No vertical overlap
	}

	return true; // Overlapping
}