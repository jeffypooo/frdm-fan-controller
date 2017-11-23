
set(PRJ_SRC main.cpp usb/usb_fan_controller.cpp usb/usb_fan_controller.h util/frdm_fc_pinout.h util/frdm_fc_io.h util/frdm_fc_io.cpp bluetooth/tinysine.h bluetooth/tinysine.cpp util/logcat.h util/logcat.cpp)
set(EXEC_NAME ${PROJECT_NAME}.elf)
add_executable(${EXEC_NAME} ${PRJ_SRC})
target_link_libraries(${EXEC_NAME} mbed)

add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
        COMMAND "${CMAKE_SIZE}" $<TARGET_FILE:${EXEC_NAME}>
        COMMENT "Size:"
        )
add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}" -Oihex $<TARGET_FILE:${EXEC_NAME}> ${PROJECT_NAME}.hex
        COMMENT "Creating hex file..."
        )
add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}" -Obinary $<TARGET_FILE:${EXEC_NAME}> ${PROJECT_NAME}.bin
        COMMENT "Creating binary file..."
        )

