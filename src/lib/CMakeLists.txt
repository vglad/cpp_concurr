cmake_minimum_required(VERSION 3.12)
project(LibConcurr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
	../../include/detail/Utils.hpp
	../../include/detail/ThreadGuard.hpp
	../../include/detail/Precompiled.hpp
	../../include/lib/lib.hpp lib.cpp
	../../include/lib/mod01/m01_3.hpp
	../../include/lib/mod01/m01_4.hpp
	../../include/lib/mod01/m01_5.hpp
	../../include/lib/mod01/m01_6.hpp
	../../include/lib/mod01/m01_7.hpp
	../../include/lib/mod01/m01_8.hpp
	../../include/lib/mod01/m01_9.hpp)

add_library(libConcurr STATIC ${SOURCE_FILES})
target_include_directories(libConcurr PRIVATE ../../include/detail ../../include/lib)
