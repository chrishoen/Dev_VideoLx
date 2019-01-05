cmake_minimum_required (VERSION 3.8)

project (VThread1 CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable (VThread1 ${SRC_FILES})

target_include_directories(VThread1 PRIVATE CommonLib)
target_link_libraries(VThread1 CommonLib)

install(TARGETS VThread1 DESTINATION bin)
