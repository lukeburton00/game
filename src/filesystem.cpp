#include "filesystem.hpp"

#include "log.hpp"
#include "whereami.h"

namespace FileSystem
{
    void setCurrentPath(std::filesystem::path path)
    {
        std::filesystem::current_path(path);
    }

    std::optional<std::filesystem::path> getExecPath()
    {
        int length, dirname_length;
        length = wai_getExecutablePath(NULL, 0, &dirname_length);
        if (length <= 0)
        {
            LOGERROR("Failed to get length for executable path.");
            return std::nullopt;
        }

        std::unique_ptr<char[]> path(new char[length + 1]);
        if (!path)
        {
            LOGERROR("Failed to allocate memory for executable path.");
            return std::nullopt;
        }

        wai_getExecutablePath(path.get(), length, &dirname_length);
        path[length] = '\0';
        path[dirname_length] = '\0';

        return path.get();
    }


    std::optional<std::filesystem::path> findDirUp(std::filesystem::path path, std::string name, const uint8_t max_levels)
    {
        int current_level = 0;

        while(!path.empty() && current_level <= max_levels)
        {
            for (auto& p : std::filesystem::directory_iterator(path))
            {
                if (p.is_directory() && p.path().filename() == name)
                {
                    return p.path();
                }
            }

            if (path == path.root_path())
                break;
            
            path = path.parent_path();
            current_level++;
        }

        return std::nullopt;
    }

    std::optional<std::filesystem::path> findDirDown(std::filesystem::path path, std::string name)
    {
        for (auto& p : std::filesystem::recursive_directory_iterator(path))
        {
            if (p.is_directory() && p.path().filename() == name)
            {
                return p.path();
            }
        }

        return std::nullopt;
    }
}