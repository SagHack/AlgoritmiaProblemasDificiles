cmake_minimum_required(VERSION 3.5)
project(LatinSquareSAT VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main
    main.cpp
    resolverCL.cpp
    generarCL.cpp
)

target_compile_options(main PRIVATE -O3)
add_subdirectory(minisat-master)
target_link_libraries(main MiniSat::libminisat)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)