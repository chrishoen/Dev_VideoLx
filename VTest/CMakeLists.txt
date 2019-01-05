cmake_minimum_required (VERSION 3.8)

project (VTest CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (VTest ${SRC_FILES})

find_package(SDL2 CONFIG REQUIRED)
target_include_directories(VTest PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(VTest ${SDL2_LIBRARIES})

install(TARGETS VTest DESTINATION "bin")
