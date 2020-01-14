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

	../../include/lib/mod03/m03_25.hpp
	../../include/lib/mod03/m03_26.hpp
	../../include/lib/mod03/m03_28.hpp
	../../include/lib/mod03/m03_29.hpp
	../../include/lib/mod03/m03_30.hpp
	../../include/lib/mod03/m03_31.hpp
	../../include/lib/mod03/m03_32.hpp
	../../include/lib/mod03/m03_33.hpp
	../../include/lib/mod03/m03_34.hpp
	../../include/lib/mod03/m03_35.hpp

	../../include/lib/mod04/m04_38.hpp
	../../include/lib/mod04/m04_39.hpp

	../../include/lib/mod05/m05_41.hpp
	../../include/lib/mod05/m05_42.hpp
	../../include/lib/mod05/m05_43.hpp
	../../include/lib/mod05/m05_44.hpp
	../../include/lib/mod05/m05_46.hpp
	../../include/lib/mod05/m05_47.hpp
	../../include/lib/mod05/m05_48.hpp
	../../include/lib/mod05/m05_50.hpp
	../../include/lib/mod05/m05_51.hpp
	../../include/lib/mod05/m05_52.hpp
	../../include/lib/mod05/m05_53.hpp
	../../include/lib/mod05/m05_54.hpp
	../../include/lib/mod05/m05_55.hpp
	../../include/lib/mod05/m05_56.hpp

	../../include/lib/mod06/m06_59.hpp
	../../include/lib/mod06/m06_60.hpp
	../../include/lib/mod06/m06_61.hpp
	../../include/lib/mod06/m06_62.hpp

	../../include/lib/lib.hpp lib.cpp
)

add_library(libConcurr STATIC ${SOURCE_FILES})
target_include_directories(libConcurr PRIVATE
	../../include/detail
	../../include/lib/mod01
	../../include/lib/mod02
	../../include/lib/mod03
	../../include/lib/mod04
	../../include/lib/mod05
	../../include/lib/mod06
	../../include/lib
)
