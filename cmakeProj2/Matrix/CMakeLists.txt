set(target matsol)

# Sources
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Set the source files to compile
file(GLOB_RECURSE sources ${source_path}/*.cpp)
file(GLOB_RECURSE headers ${include_path}/*.h)

# Build library
add_library(${target} STATIC ${sources})

# Add include directories
target_include_directories(${target} PUBLIC ${include_path})

install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/x64/include)

install(TARGETS ${target}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/x64/lib)