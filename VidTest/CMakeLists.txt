cmake_minimum_required (VERSION 3.8)

project (VidTest CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (VidTest ${SRC_FILES})

target_include_directories(VidTest PRIVATE CommonLib)
target_link_libraries(VidTest CommonLib)

install(TARGETS VidTest DESTINATION "bin")
