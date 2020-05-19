SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1.0.0)

SET(RPI_TOOLCHAIN "")
SET(TOOLCHAIN_ROOT ${RPI_TOOLCHAIN}/tools/arm-bcm2708/arm-bcm2708-linux-gnueabi)
SET(TOOLCHAIN_SYSROOT ${TOOLCHAIN_ROOT}/arm-bcm2708-linux-gnueabi/sysroot)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${TOOLCHAIN_ROOT}/bin/arm-bcm2708-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_ROOT}/bin/arm-bcm2708-linux-gnueabi-g++)
SET(CMAKE_STRIP		   ${TOOLCHAIN_ROOT}/bin/arm-bcm2708-linux-gnueabi-strip CACHE STRING "" FORCE)
SET(CMAKE_AR   	       ${TOOLCHAIN_ROOT}/bin/arm-bcm2708-linux-gnueabi-ar CACHE STRING "" FORCE)

SET(CMAKE_SYSROOT ${TOOLCHAIN_SYSROOT})
SET(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_SYSROOT})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
