add_executable(example main.cpp)

set(headers ${PROJECT_SOURCE_DIR}/Matrix/include)

include_directories(example PUBLIC ${headers})
target_link_libraries(example matsol)

set_target_properties(example 
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)  