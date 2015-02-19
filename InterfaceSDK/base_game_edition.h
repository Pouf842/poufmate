#ifndef __BASE_GAME_EDITION_
#define __BASE_GAME_EDITION_

#include "base_board.h"

class BaseGameEdition
{
public:
	BaseGameEdition(void);
	~BaseGameEdition(void);
	
	BaseBoard oGetBaseBoard() const;

protected :
	BaseBoard moBaseBoard;
};

#endif