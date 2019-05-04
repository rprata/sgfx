set(SRC 
	utils/ibutterfree_upng.c
	utils/ibutterfree_config.c
	utils/ibutterfree_error_handler.c
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
	target_link_libraries(ibutterfree pthread)
endif()

if(${LUA_SUPPORT})
	if(${LUA_VERSION} EQUAL 52)
		target_link_libraries(ibutterfree lua5.2)
		add_definitions(-DLUA_5_2)
		if(NOT DEFINED ${LUA_INCLUDES})
			set(LUA_INCLUDES /usr/include/lua5.2)
		endif()
	elseif(${LUA_VERSION} EQUAL 51)
		target_link_libraries(ibutterfree lua5.1)
		add_definitions(-DLUA_5_1)
		if(NOT DEFINED ${LUA_INCLUDES})
			set(LUA_INCLUDES /usr/include/lua5.1)
		endif()
	endif()
endif()

target_include_directories (ibutterfree PUBLIC
		${PROJECT_SOURCE_DIR}/includes/core
		${PROJECT_SOURCE_DIR}/includes/utils
if(${LUA_SUPPORT})
		${LUA_INCLUDES}
endif()
	)

set_target_properties(ibutterfree PROPERTIES 
					VERSION ${IBUTTERFREE_VERSION_STRING} 
					SOVERSION ${IBUTTERFREE_VERSION_MAJOR} 
					DESCRIPTION ${IBUTTERFREE_DESCRIPTION} 
					)

if(CMAKE_STRIP)
	add_custom_command( TARGET ibutterfree POST_BUILD COMMAND ${CMAKE_STRIP} -s *${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()

add_custom_target(link_target ALL
					COMMAND ${CMAKE_COMMAND} -E create_symlink "libibutterfree.so" "ibutterfree.so")