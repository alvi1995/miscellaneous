set(target fraction)

# Sources
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Set the source files to compile
file(GLOB_RECURSE sources ${source_path}/*.cpp)
file(GLOB_RECURSE headers ${include_path}/*.h)

# Build library
add_library(${target} ${sources})

# Add include directories
target_include_directories(${target} PUBLIC ${include_path})

install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${target})

install(TARGETS ${target}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
