SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1.0.0)

SET(TOOLCHAIN_ROOT /home/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf)
SET(TOOLCHAIN_SYSROOT ${TOOLCHAIN_ROOT}/arm-linux-gnueabihf/sysroot)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${TOOLCHAIN_ROOT}/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_ROOT}/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_STRIP		   ${TOOLCHAIN_ROOT}/bin/arm-linux-gnueabihf-strip CACHE STRING "" FORCE)
SET(CMAKE_AR   	       ${TOOLCHAIN_ROOT}/bin/arm-linux-gnueabihf-ar CACHE STRING "" FORCE)

SET(CMAKE_SYSROOT ${TOOLCHAIN_SYSROOT})
SET(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_SYSROOT})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
