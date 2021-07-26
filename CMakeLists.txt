cmake_minimum_required(VERSION 3.19)

set(This CurrencyApp)
project(${This} C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
        CurrencyApp.hpp
        )

set(Sources
        CurrencyApp.cpp
        )

add_library(${This} SHARED ${Sources} ${Headers})
add_executable(run ${Sources} ${Headers})

add_subdirectory(test)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(nlohmann_json_cmake_fetchcontent)


target_link_libraries(run nlohmann_json::nlohmann_json
        ${CURL_LIBRARIES}
        )
target_link_libraries(${This} nlohmann_json::nlohmann_json
        ${CURL_LIBRARIES})