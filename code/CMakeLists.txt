cmake_minimum_required(VERSION 3.14)
project(LPE-SW CXX C ASM)

include("${CMAKE_CURRENT_LIST_DIR}/ufsel/cmake/QueryRepositoryState.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ufsel/cmake/BitOperations.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ufsel/cmake/Units.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ufsel/cmake/Itertools.cmake")

set(SRC
        src/main.cpp
        src/gpio.cpp
        src/timer.cpp
        src/adc.cpp
        src/flash.cpp
        src/entry_point.cpp
        )

add_executable(${PROJECT_NAME}.elf ${SRC} ${CAN_SRC})

target_include_directories(${PROJECT_NAME}.elf PRIVATE
        Drivers/
        .
        ufsel/include
        )



set(HEX_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(
        POST_BUILD
        TARGET ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        # COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

add_custom_command(
        POST_BUILD
        TARGET ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
        )

add_custom_command(
      POST_BUILD
      TARGET ${PROJECT_NAME}.elf
      WORKING_DIRECTORY ..
      COMMAND bash ./disassemble.sh
)

