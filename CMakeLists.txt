cmake_minimum_required(VERSION 3.12)
project(air-hockey)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(air_hockey src/main.cpp src/AirHockey.cpp src/Renderer.cpp src/OpenGLFunctions.cpp src/Puck.cpp src/Paddle.cpp)
include_directories(BEFORE .)
if(LINUX OR MSVC)
target_link_libraries(air_hockey GL SDL2 SDL2_image)
elseif(APPLE)
include_directories(BEFORE /opt/homebrew/include)
target_link_directories(air_hockey BEFORE PUBLIC /opt/homebrew/lib)
target_link_libraries(air_hockey SDL2 SDL2_image)
endif()
target_compile_options(air_hockey PUBLIC -g -Wfatal-errors -Wextra -Wall -pedantic -Wconversion)
file(COPY shaders DESTINATION .)
file(COPY assets DESTINATION .)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  hello_test
  tests/hello_test.cc
  src/AirHockey.cpp
  src/Renderer.cpp
  src/OpenGLFunctions.cpp
	src/Puck.cpp
	src/Paddle.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  SDL2
  SDL2_image
)
target_link_directories(hello_test BEFORE PUBLIC /opt/homebrew/lib)

include(GoogleTest)
gtest_discover_tests(hello_test)
