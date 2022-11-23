set(target operation)

# Sources
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Set the source files to compile
file(GLOB_RECURSE sources ${source_path}/*.cpp)
file(GLOB_RECURSE headers ${include_path}/*.h)

add_library(${target} ${sources})
target_link_libraries(${target} fraction)

# Add include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${target})
install(TARGETS ${target}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )