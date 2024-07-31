#pragma once

#include <filesystem>
#include <optional>

namespace FileSystem 
{
    void setCurrentPath(const std::filesystem::path& path);
    std::optional<std::filesystem::path> getExecPath();
    std::optional<std::filesystem::path> findDirUp(std::filesystem::path path, const std::string& name, const uint8_t max_levels);
    std::optional<std::filesystem::path> findDirDown(const std::filesystem::path& path, const std::string& name);
}

