cmake_minimum_required (VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
add_executable(rutka "rutka.cpp")

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()