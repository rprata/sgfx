cmake_minimum_required (VERSION 2.8.11)
project (SGFX)
set(SGFX_DESCRIPTION "SGFX is a lightweight embedded library for displays and touchscreens providing everything required to build a fully featured embedded GUI.")
set(SGFX_VERSION_MAJOR 1)
set(SGFX_VERSION_MINOR 0)
set(SGFX_VERSION_PATCH 0)
set(SGFX_VERSION_STRING ${SGFX_VERSION_MAJOR}.${SGFX_VERSION_MINOR}.${SGFX_VERSION_PATCH})

set(POSIX_SUPPORT 1)
set(LUA_SUPPORT 0)
set(LUA_VERSION 53)

add_subdirectory (src)
add_subdirectory (examples)