#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/std.h"

#define LOGCRITICAL(...) spdlog::critical(__VA_ARGS__)

#ifndef NDEBUG
	#define LOGINFO(...) spdlog::info(__VA_ARGS__)
	#define LOGWARN(...) spdlog::warn(__VA_ARGS__)
	#define LOGERROR(...) spdlog::error(__VA_ARGS__)
#else
	#define LOGINFO(...)
	#define LOGWARN(...)
    #define LOGERROR(...)
#endif
