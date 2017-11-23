cmake_minimum_required(VERSION 3.8)

project(frdm-fan-control ASM C CXX)

##################################
#        Compiler setup          #
##################################

# Flags common to all targets/build variants
set(COMMON_COMPILER_FLAGS "-Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fexceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")
# Debug specfic flags
set(DEBUG_COMPILER_FLAGS "-O0 -g3 -DMBED_DEBUG -DMBED_TRAP_ERRORS_ENABLED=1")
# Release specific flags
set(RELEASE_COMPILER_FLAGS "-Os -NDEBUG")
# Assembler flags
set(CMAKE_ASM_FLAGS "${COMMON_COMPILER_FLAGS} -x assembler-with-cpp")
# C flags
set(CMAKE_C_FLAGS "${COMMON_COMPILER_FLAGS} -std=gnu11")
# C++ flags (and linker flags)
set(CMAKE_CXX_FLAGS "${COMMON_COMPILER_FLAGS} -std=gnu++11 -fno-rtti")
set(LINKER_SCRIPT "/home/jeff/development/personal/mbed/frdm-fan-controller/ext/mbed-os-lib/mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-wchar-size-warning -Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,malloc_r -Wl,--wrap,free_r -Wl,--wrap,realloc_r -Wl,--wrap,memalign_r -Wl,--wrap,calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -static --specs=nosys.specs -T${LINKER_SCRIPT}")

##################################
#           Includes             #
##################################

set(SYS_LOCAL ${CMAKE_SYSROOT}/local/include)
set(MBED_ROOT ext/mbed-os-lib/mbed-os)
set(MBED_TARGET ${MBED_ROOT}/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM)

message(STATUS "Include paths:")
message(STATUS "\tMBED_ROOT: ${MBED_ROOT}")
message(STATUS "\tMBED_TARGET: ${MBED_TARGET}")

include_directories(${MBED_ROOT} ${MBED_TARGET})

##################################
#           Subdirs              #
##################################
add_subdirectory(ext)
add_subdirectory(src)

