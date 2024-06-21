cmake_minimum_required(VERSION 3.28)

project(game)

set(SRC
	"${CMAKE_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c"
)

add_executable(${PROJECT_NAME} ${SRC})

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(OpenGL REQUIRED)

add_subdirectory("vendor/glm")
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/spdlog")

target_include_directories(${PROJECT_NAME}
	PRIVATE "vendor/glm"
	PRIVATE "vendor/glad/include"
	PRIVATE "vendor/glfw/include"
	PRIVATE "vendor/spdlog/include"
)

target_link_libraries(${PROJECT_NAME}
	glm::glm
	glfw
	spdlog::spdlog
	${OPENGL_LIBRARIES}
)