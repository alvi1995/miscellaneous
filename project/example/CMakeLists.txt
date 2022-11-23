add_executable(example1 main.cpp)

set(headers ${PROJECT_SOURCE_DIR}/operation/include)

include_directories(example1 PUBLIC ${headers})
target_link_libraries(example1 fraction operation)