cmake_minimum_required(VERSION 3.5)
project(clorx-project VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include /usr/local/include)

add_executable(main
  src/main.cpp
)

add_executable(defun
  src/defun.cpp
)

set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")

# Indication to the code that this is a debug build
if (${IS_DEBUG_BUILD})
    # set compiler flags
    set(CMAKE_CXX_FLAGS "-O0 -Wall")
    add_compile_definitions(TEST_DEBUG)
else()
    # set compiler flags
    set(CMAKE_CXX_FLAGS "-O2")
endif()

target_link_libraries(main
    PRIVATE
    #assummes an installation
        ecl
        dl
)

target_link_libraries(defun
    PRIVATE
    #assummes an installation
        ecl
)