cmake_minimum_required(VERSION 3.12)
project(LibConcurr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
	../../include/detail/Utils.hpp
	../../include/detail/ThreadGuard.hpp
	../../include/detail/Precompiled.hpp
	../../include/lib/mod01/m01_03.hpp
	../../include/lib/mod01/m01_04.hpp
	../../include/lib/mod01/m01_05.hpp
	../../include/lib/mod01/m01_06.hpp
	../../include/lib/mod01/m01_07.hpp
	../../include/lib/mod01/m01_08.hpp
	../../include/lib/mod01/m01_09.hpp
	../../include/lib/mod01/m01_10.hpp
	../../include/lib/mod01/m01_11.hpp
	../../include/lib/mod01/m01_12.hpp
	../../include/lib/mod01/m01_13.hpp
	../../include/lib/mod01/m01_14.hpp
	../../include/lib/mod01/m01_15.hpp

	../../include/lib/mod02/m02_18.hpp
	../../include/lib/mod02/m02_19.hpp
	../../include/lib/mod02/m02_22.hpp
	../../include/lib/mod02/m02_23.hpp
	../../include/lib/mod02/m02_24.hpp
	
	../../include/lib/lib.hpp lib.cpp)

add_library(libConcurr STATIC ${SOURCE_FILES})
target_include_directories(libConcurr PRIVATE
		../../include/detail
		../../include/lib/mod01
		../../include/lib/mod02
		../../include/lib
		)
