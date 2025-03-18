cmake_minimum_required(VERSION 3.2)
project(jebi C CXX ASM)

add_library(jebi STATIC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(
    ${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32g474xx.s"
)
    
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
    
set(JEBI_DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../jebi_drivers)

add_subdirectory(${JEBI_DRIVERS_DIR} ${CMAKE_BINARY_DIR}/jebi_drivers_build_${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC jebi_drivers)