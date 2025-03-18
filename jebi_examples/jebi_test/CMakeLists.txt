cmake_minimum_required(VERSION 3.2)
project(example_jebi_test C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${SOURCES}
    "main.cpp"
)
    
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/jebi/include"
)
    
set(JEBI_DIR ${CMAKE_SOURCE_DIR}/../../jebi) 

add_subdirectory(${JEBI_DIR} ${CMAKE_BINARY_DIR}/jebi_drivers_build_${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-Wl,-Map,${PROJECT_NAME}.map"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC jebi)
