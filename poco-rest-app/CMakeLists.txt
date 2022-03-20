cmake_minimum_required(VERSION 3.2)

project(poco-rest-app C CXX)

find_package(GTest REQUIRED)
find_package(Threads)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)

include_directories(${Poco_INCLUDE_DIRS})
link_directories("/usr/local/lib")

SET (SERVER_BINARY "server")

file(GLOB HTTP_SERVER_SOURCES "http_server/*.cpp")

add_executable(${SERVER_BINARY} ${HTTP_SERVER_SOURCES} main.cpp)
add_executable(gtests tests.cpp)

target_include_directories(${SERVER_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(gtests PRIVATE "${CMAKE_BINARY_DIR}")

target_compile_options(${SERVER_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_options(gtests PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(${SERVER_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES})
target_link_libraries(gtests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

set_target_properties(${SERVER_BINARY} gtests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${SERVER_BINARY} gtests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

install(TARGETS ${SERVER_BINARY} RUNTIME DESTINATION bin)

enable_testing()
add_test(gtests gtests)