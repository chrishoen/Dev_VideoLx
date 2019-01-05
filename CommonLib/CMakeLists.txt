cmake_minimum_required (VERSION 3.8)

project (CommonLib CXX)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_library (CommonLib STATIC ${SRC_FILES})
target_include_directories(CommonLib PUBLIC ${PROJECT_SOURCE_DIR})

find_package(RisLib CONFIG REQUIRED)
target_include_directories(CommonLib PUBLIC RisLib)
target_link_libraries(CommonLib RisLib)

add_library(wiringPi SHARED IMPORTED)
set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libwiringPi.so")
target_link_libraries(CommonLib wiringPi)
target_include_directories(CommonLib PUBLIC "/usr/local/include")

find_package(SDL2 CONFIG REQUIRED)
target_include_directories(CommonLib PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(CommonLib ${SDL2_LIBRARIES})








if (0)
add_library(SDL2 STATIC IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libSDL2.a")
target_link_libraries(CommonLib SDL2)

add_library(SDL2_image STATIC IMPORTED)
set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libSDL2_image.a")
target_link_libraries(CommonLib SDL2_image)

target_include_directories(CommonLib PUBLIC "/usr/local/include/SDL2")
endif()
