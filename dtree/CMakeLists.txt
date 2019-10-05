cmake_minimum_required(VERSION 3.10)

project(dtree VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(DTREE_SOURCES
        src/dtree.cpp
)

add_library(${PROJECT_NAME} SHARED ${DTREE_SOURCES})

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(main dtree)

add_dependencies(main dtree)