#ifndef __POSITION_H_
#define __POSITION_H_

/**
 * This class describes a position on the board
 * by two coordinates : X and Y
 * WARNING : X is the vertical coordinates, and Y the horizontal
 */

#include <string>

class Position
{
  public :
	int mX;	// The x coordinate (vertical)
	int mY;	// The y coordinate (horizontal)
	bool mbEmpty;	// A boolean specifying if the position is empty (not filled yet)

	/**
	 * Constructor. Construct an empty position
	 */
	Position();

	/**
	 * Constructor
	 */
	Position(unsigned int X, unsigned int Y);

	/**
	 * Copy constructor
	 */
	Position(const Position & oPos);

	/**
	 * Constructor. The string contains the x and y
	 * coordinates, as "XY". If it's longer, the
	 * rest is ignored
	 */
	Position(std::string strCoords);

	/**
	 * Return true if the position is (empty) uninitialized
	 */
	bool bIsEmpty();

	/**
	 * Empty the position
	 */
	void Empty();

	/**
	 * Operator = with string.
	 * Same as the Position(std::string) constructor
	 */
	Position & operator=(std::string strCoords);

	/**
	 * Equality comparator
	 */
	bool operator==(const Position & oPos);

	/**
	 * Difference comparator
	 */
	bool operator!=(const Position & oPos);
};

#endif