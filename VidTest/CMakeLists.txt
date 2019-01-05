cmake_minimum_required (VERSION 3.8)

project (VideoTest CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (VideoTest ${SRC_FILES})

target_include_directories(VideoTest PRIVATE CommonLib)
target_link_libraries(VideoTest CommonLib)

install(TARGETS VideoTest DESTINATION bin)
