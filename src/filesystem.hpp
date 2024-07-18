#pragma once

#include <filesystem>
#include <optional>

namespace FileSystem 
{
    void setCurrentPath(std::filesystem::path path);

    std::optional<std::filesystem::path> getExecPath();
    std::optional<std::filesystem::path> findDirUp(std::filesystem::path path, std::string name, const uint8_t max_levels);
    std::optional<std::filesystem::path> findDirDown(std::filesystem::path path, std::string name);
}

