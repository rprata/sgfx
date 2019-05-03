cmake_minimum_required (VERSION 2.8.11)
project (IBUTTERFREE)

set(POSIX_SUPPORT 0)
set(LUA_SUPPORT 1)

add_subdirectory (src)
add_subdirectory (examples)