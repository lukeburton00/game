#include "game.hpp"
#include "log.hpp"

int main(int argc, char** argv)
{
	Game game;
	if (!game.start())
	{
		LOGCRITICAL("Failed to start game.");
		exit(1);
	}

    return 0;
}