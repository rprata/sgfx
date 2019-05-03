set(SRC 
	utils/ibutterfree_upng.c
	utils/ibutterfree_config.c
	core/ibutterfree.c
	core/ibutterfree_surface.c
	core/ibutterfree_draw.c
	core/ibutterfree_image.c
	core/ibutterfree_font.c
	core/ibutterfree_event.c
	)

if(${LUA_SUPPORT})
	set(SRC ${SRC} core/ibutterfree_lua.c)
endif()

add_library(ibutterfree SHARED ${SRC})

set(CMAKE_C_FLAGS "-Wall -Werror -O3")

if(${POSIX_SUPPORT})
	add_definitions(-D__POSIX__)
	set(ibutterfree pthread)	
endif()

if(${LUA_SUPPORT})
	target_link_libraries(ibutterfree lua5.1)
endif()

target_include_directories (ibutterfree PUBLIC
		${PROJECT_SOURCE_DIR}/includes/core
		${PROJECT_SOURCE_DIR}/includes/utils
		)

if(CMAKE_STRIP)
	add_custom_command( TARGET ibutterfree POST_BUILD COMMAND ${CMAKE_STRIP} -s *${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()