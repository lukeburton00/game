cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(game)

set(SRC
 "vendor/glad/src/glad.c"
 "vendor/stb/stb_image.cpp"
 "src/main.cpp"
 "src/game.cpp"
 "src/input.cpp"
 "src/window.cpp"
 "src/renderer.cpp"
 "src/shader.cpp"
 "src/texture.cpp")


add_executable(${PROJECT_NAME} ${SRC})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()


add_subdirectory("vendor/glm")
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/spdlog")

target_include_directories(${PROJECT_NAME}
	PRIVATE "vendor/glm"
	PRIVATE "vendor/glad/include"
	PRIVATE "vendor/glfw/include"
	PRIVATE "vendor/spdlog/include"
	PRIVATE "vendor/stb"
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
	glm::glm
	glfw
	spdlog::spdlog
	${OPENGL_LIBRARIES}
)
