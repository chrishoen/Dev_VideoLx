cmake_minimum_required (VERSION 3.8)

project (Test CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (Test ${SRC_FILES})

find_package(RisLib CONFIG REQUIRED)

target_include_directories(Test PRIVATE RisLib)
target_link_libraries(Test RisLib)
