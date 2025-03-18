cmake_minimum_required(VERSION 3.2)
project(jebi_drivers C CXX ASM)

add_library(jebi_drivers STATIC)

file(
    GLOB_RECURSE HAL_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx-hal-driver/Src/*.c
)

set(CMAKE_CXX_STANDARD 17)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${HAL_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-g4/Source/Templates/system_stm32g4xx.c"
)

target_compile_definitions(
    ${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:DEBUG>"
    "$<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:STM32G474xx>"
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_5/CMSIS/Core/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx-hal-driver/Inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-g4/Include"
)

target_compile_options(
    ${PROJECT_NAME} PUBLIC
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    "$<$<CONFIG:Debug>:-g3>"
    "$<$<NOT:$<CONFIG:Debug>>:-g0>"
    "$<$<NOT:$<CONFIG:Debug>>:-Os>"
)

target_link_options(
    ${PROJECT_NAME} PUBLIC
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -T
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32G474VETX_FLASH.ld
)