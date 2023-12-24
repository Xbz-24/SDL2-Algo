cmake_minimum_required(VERSION 3.25)
project(AlgoVisualizer)
set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost REQUIRED COMPONENTS container graph)
find_package(fmt REQUIRED)

message("SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message("SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
message("SDL2_TTF_INCLUDE_DIRS: ${SDL2_TTF_INCLUDE_DIRS}")
message("SDL2_TTF_LIBRARIES: ${SDL2_TTF_LIBRARIES}")
message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARIES: ${Boost_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_library(boost_container_wrapper INTERFACE)
target_link_libraries(boost_container_wrapper INTERFACE Boost::container)

add_executable(AlgoVisualizer main.cpp Visualizer.cpp Visualizer.hpp Maze.cpp Maze.hpp FPSCounter.cpp FPSCounter.hpp MazeRenderer.cpp MazeRenderer.hpp)

target_link_libraries(AlgoVisualizer ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} Boost::graph boost_container_wrapper fmt::fmt)

if(MSVC)
    target_compile_options(AlgoVisualizer PRIVATE
            /W4
            /WX
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
            /w15038
            )
else()
    target_compile_options(AlgoVisualizer PRIVATE
            -Wall
            -Wextra
            -pedantic
            -Werror
            -Weffc++
            -Wconversion
            -Wsign-conversion
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wnull-dereference
            -Wuseless-cast
            -Wdouble-promotion
            -Wformat=2
            -Wshadow
            -Wfloat-equal
            -Wcast-align
            -Wcast-qual
            -Wwrite-strings
            -Wmissing-declarations
            -Woverloaded-virtual
            -Wnoexcept
            -Wnon-virtual-dtor
            -Wstrict-overflow=5
            -Wswitch-default
            -Wswitch-enum
            -Winit-self
            -Wredundant-decls
            -Wundef
            -Winline
            -Wunreachable-code
            -Wdeprecated
            -Wsuggest-override
            )
endif()