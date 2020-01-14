cmake_minimum_required (VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT MSVC)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
endif()

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})

if (NOT MSVC)
    target_link_libraries(main PRIVATE Threads::Threads)
endif()

target_link_libraries(main PRIVATE libConcurr)
target_include_directories(main PRIVATE
        ../include/detail
        ../include/lib/mod01
        ../include/lib/mod02
        ../include/lib/mod03
        ../include/lib/mod04
        ../include/lib/mod05
        ../include/lib/mod06
        ../include/lib
)
