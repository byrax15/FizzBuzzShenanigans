# CMakeList.txt : CMake project for FizzBuzzShenanigans++, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)
project ("FizzBuzzShenanigans++")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Add source to this project's executable.
add_executable (FizzBuzzShenanigans++ "main.cpp")
add_executable (Benchmarks "benchmarks.cpp")

# TODO: Add tests and install targets if needed.
find_package(benchmark CONFIG REQUIRED)
target_link_libraries(Benchmarks PRIVATE benchmark::benchmark benchmark::benchmark_main)


if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FizzBuzzShenanigans++)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Benchmarks)
endif ()