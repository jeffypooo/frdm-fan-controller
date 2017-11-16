

file(GLOB CMSIS_SRC
        "mbed-os/cmsis/*.h"
        "mbed-os/cmsis/TARGET_CORTEX_M/*.h"
        "mbed-os/cmsis/TARGET_CORTEX_M/TOOLCHAIN_GCC/*.h"
        )
file(GLOB DRIVERS_SRC
        "mbed-os/drivers/*.h"
        "mbed-os/drivers/*.cpp"
        )
file(GLOB USB_SRC
        "mbed-os/features/unsupported/USBDevice/targets/TARGET_Freescale/*.h"
        "mbed-os/features/unsupported/USBDevice/targets/TARGET_Freescale/*.cpp"
        "mbed-os/features/unsupported/USBDevice/USBDevice/*.h"
        "mbed-os/features/unsupported/USBDevice/USBDevice/*.cpp"
        "mbed-os/features/unsupported/USBDevice/USBHID/*.h"
        "mbed-os/features/unsupported/USBDevice/USBHID/USBHID.cpp"
        )
file(GLOB HAL_SRC
        "mbed-os/hal/*.h"
        "mbed-os/hal/*.c"
        "mbed-os/hal/storage_abstraction/*.h"
        )
file(GLOB PLATFORM_SRC
        "mbed-os/platform/*.h"
        "mbed-os/platform/*.c"
        "mbed-os/platform/*.cpp"
        )
file(GLOB RTOS_SRC
        "mbed-os/rtos/*.h"
        "mbed-os/rtos/*.cpp"
        "mbed-os/rtos/TARGET_CORTEX/*.h"
        "mbed-os/rtos/TARGET_CORTEX/*.c"
        "mbed-os/rtos/TARGET_CORTEX/*.cpp"
        "mbed-os/rtos/TARGET_CORTEX/rtx5/*.h"
        "mbed-os/rtos/TARGET_CORTEX/rtx5/*.c"
        "mbed-os/rtos/TARGET_CORTEX/rtx5/TARGET_RTOS_M4_M7/TOOLCHAIN_GCC/*.S"
        )
file(GLOB TARGET_SRC
        "mbed-os/targets/TARGET_Freescale/mbed_rtx.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/fsl_common.c"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/*.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api/*.c"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/*.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/*.c"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/*.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/*.c"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/TOOLCHAIN_GCC_ARM/startup_MK64F12.S"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/*.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/*.c"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/*.h"
        "mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM/*.c"
        )
set(MBED_ALL_SRC ${CMSIS_SRC} ${DRIVERS_SRC} ${USB_SRC} ${HAL_SRC} ${PLATFORM_SRC} ${RTOS_SRC} ${TARGET_SRC})

# Defines used by mbed-os
set(MBED_MACROS
        -DMBED_CONF_RTOS_PRESENT=1
        -DMBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE=9600
        -DFEATURE_LWIP=1
        -D__MBED__=1
        -DDEVICE_I2CSLAVE=1
        -D__FPU_PRESENT=1
        -DTARGET_Freescale
        -DDEVICE_PORTINOUT=1
        -DTARGET_RTOS_M4_M7
        -DDEVICE_LOWPOWERTIMER=1
        -DDEVICE_RTC=1
        -DTOOLCHAIN_object
        -DDEVICE_SERIAL_ASYNCH=1
        -D__CMSIS_RTOS
        -DFSL_RTOS_MBED
        -DDEVICE_STORAGE=1
        -DTARGET_KPSDK_MCUS
        -DTOOLCHAIN_GCC
        -DTARGET_CORTEX_M
        -DTARGET_KSDK2_MCUS
        -DTARGET_LIKE_CORTEX_M4
        -DDEVICE_ANALOGOUT=1
        -DTARGET_M4
        -DTARGET_UVISOR_UNSUPPORTED
        -DTARGET_K64F
        -DDEVICE_SPI_ASYNCH=1
        -DDEVICE_PWMOUT=1
        -DDEVICE_INTERRUPTIN=1
        -DTARGET_CORTEX
        -DDEVICE_I2C=1
        -DDEVICE_PORTOUT=1
        -D__CORTEX_M4
        -DDEVICE_STDIO_MESSAGES=1
        -DCPU_MK64FN1M0VMD12
        -DTARGET_LIKE_MBED
        -DTARGET_FF_ARDUINO
        -DTARGET_KPSDK_CODE
        -DTARGET_RELEASE
        -DDEVICE_SERIAL_FC=1
        -DFEATURE_STORAGE=1
        -DDEVICE_TRNG=1
        -D__MBED_CMSIS_RTOS_CM
        -DDEVICE_SLEEP=1
        -DTOOLCHAIN_GCC_ARM
        -DMBED_BUILD_TIMESTAMP=1510536615.63
        -DTARGET_FRDM
        -DTARGET_MCUXpresso_MCUS
        -DDEVICE_SPI=1
        -DDEVICE_SPISLAVE=1
        -DDEVICE_ANALOGIN=1
        -DDEVICE_SERIAL=1
        -DDEVICE_FLASH=1
        -DDEVICE_PORTIN=1
        -DTARGET_MCU_K64F
        -DARM_MATH_CM4)
add_library(mbed STATIC ${MBED_ALL_SRC})
target_include_directories(mbed PUBLIC
        mbed-os
        mbed-os/cmsis
        mbed-os/cmsis/TARGET_CORTEX_M/
        mbed-os/cmsis/TARGET_CORTEX_M/TOOLCHAIN_GCC
        mbed-os/drivers
        mbed-os/features/unsupported/USBDevice/targets/TARGET_Freescale
        mbed-os/features/unsupported/USBDevice/USBDevice
        mbed-os/features/unsupported/USBDevice/USBHID
        mbed-os/hal
        mbed-os/hal/storage_abstraction
        mbed-os/platform
        mbed-os/rtos
        mbed-os/rtos/TARGET_CORTEX
        mbed-os/rtos/TARGET_CORTEX/rtx5
        mbed-os/targets
        mbed-os/targets/TARGET_Freescale
        mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api
        mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F
        mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device
        mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers
        mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM
)
target_compile_options(mbed PUBLIC "$<$<CONFIG:DEBUG>:${MBED_MACROS}${COMMON_FLAGS}>")
#set_target_properties(mbed PROPERTIES LINK_DEPENDS ../ext/mbed-os-lib/mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld)
