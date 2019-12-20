#include "Def.h"
#include "Proto.h"

GameState gamestate = MENUSTATE;

int main()
{
	WindowSize();
	while (gamestate != ENDSTATE)

switch (gamestate)
	{
		case MENUSTATE:
					gamestate = menu();
	break;

		case PLAYSTATE:
					gamestate = theMoves();
	break;
	
		case EVENTSTATE:
			gamestate = roomEvent();
	break;

		case GAMEOVER:
			gamestate = gameOver();
	break;
		case WINNINGSTATE:
			gamestate = winning();
	break;
		case ENDSTATE:

	break;
	}

return 0;
}