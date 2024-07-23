#include "game.hpp"

#include "log.hpp"
#include "filesystem.hpp"

int main(int argc, char** argv)
{
    auto exec_path = FileSystem::getExecPath();
    if (exec_path.has_value())
    {
        LOGINFO("Executable path: {}", exec_path.value().string());
    }

    else
    {
        LOGCRITICAL("Could not find executable path.");
        return 1;
    }

    auto assets_path = FileSystem::findDirUp(exec_path.value(), "assets", 2);
    if (assets_path.has_value())
    {
        FileSystem::setCurrentPath(assets_path.value());
        LOGINFO("Assets path: {}", assets_path.value().string());
    }

    else
    {
        LOGCRITICAL("Could not find assets path.");
        return 1;
    }

	Game game;
	if (!game.start())
	{
		LOGCRITICAL("Failed to start game.");
		return 1;
	}

    return 0;
}
