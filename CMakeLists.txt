cmake_minimum_required (VERSION 2.8.11)
project (IBUTTERFREE)
set(IBUTTERFREE_DESCRIPTION "IButterFree is a lightweight embedded library for displays and touchscreens providing everything required to build a fully featured embedded GUI.")
set(IBUTTERFREE_VERSION_MAJOR 0)
set(IBUTTERFREE_VERSION_MINOR 1)
set(IBUTTERFREE_VERSION_PATCH 0)
set(IBUTTERFREE_VERSION_STRING ${IBUTTERFREE_VERSION_MAJOR}.${IBUTTERFREE_VERSION_MINOR}.${IBUTTERFREE_VERSION_PATCH})

set(POSIX_SUPPORT 1)
set(LUA_SUPPORT 1)
set(LUA_VERSION 51)

add_subdirectory (src)
add_subdirectory (examples)