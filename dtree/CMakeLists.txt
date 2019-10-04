cmake_minimum_required(VERSION 3.10)

project(dtree VERSION 0.1 LANGUAGES CXX)

set(YDL_SOURCES
        src/dtree.cpp
        src/parser.cpp
)

add_library(${PROJECT_NAME} SHARED ${YDL_SOURCES})

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(main dtree)

add_dependencies(main dtree)