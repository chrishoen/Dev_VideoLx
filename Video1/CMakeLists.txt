cmake_minimum_required (VERSION 3.8)

project (Video1 CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (Video1 ${SRC_FILES})

find_package(SDL2 CONFIG REQUIRED)
target_include_directories(Video1 PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(Video1 ${SDL2_LIBRARIES})

install(TARGETS Video1 DESTINATION "bin")
