cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 99)
project(linlog VERSION 0.0.1 LANGUAGES C)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pthread")

add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/libzmq)
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/libconfig)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE config zmq pthread)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/third-party/libzmq/ DESTINATION /usr/lib/${PROJECT_NAME}/libzmq)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/third-party/libconfig/ DESTINATION /usr/lib/${PROJECT_NAME}/libconfig)