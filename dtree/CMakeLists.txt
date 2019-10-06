cmake_minimum_required(VERSION 3.10)

project(dtree VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(DTREE_SOURCES
        src/dtree.cpp
)

set(TARGET_EXEC main)

add_library(${PROJECT_NAME} SHARED ${DTREE_SOURCES})

add_executable(${TARGET_EXEC} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${TARGET_EXEC} dtree)

add_dependencies(${TARGET_EXEC} dtree)

# use OpenMP if available
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${TARGET_EXEC} OpenMP::OpenMP_CXX)
endif()