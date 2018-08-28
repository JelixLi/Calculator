cmake_minimum_required(VERSION 2.8.7)
project(calculator)

add_compile_options(-fpermissive)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY build)


file(GLOB_RECURSE CPP_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp )
file(GLOB_RECURSE H_LIST ${PROJECT_SOURCE_DIR}/include/*.h)
list(REMOVE_ITEM CPP_LIST main.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include")

ADD_LIBRARY(cal-static STATIC ${CPP_LIST} ${H_LIST})


ADD_EXECUTABLE(calTest test/main.cpp)
target_link_libraries(calTest cal-static)



