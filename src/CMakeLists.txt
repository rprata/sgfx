set(SRC 
	utils/sgfx_upng.c
	utils/sgfx_config.c
	utils/sgfx_error_handler.c
	core/sgfx.c
	core/sgfx_surface.c
	core/sgfx_draw.c
	core/sgfx_image.c
	core/sgfx_font.c
	core/sgfx_event.c
	)

if(${LUA_SUPPORT})
	set(SRC ${SRC} core/sgfx_lua.c)
endif()

add_library(sgfx SHARED ${SRC})

set(CMAKE_C_FLAGS "-Wall -Werror -O3")

if(${POSIX_SUPPORT})
	add_definitions(-D__POSIX__)
	target_link_libraries(sgfx pthread)
endif()

if(${LUA_SUPPORT})
	if(${LUA_VERSION} EQUAL 53)
		target_link_libraries(sgfx lua5.3)
		add_definitions(-DLUA_5_2)
		if(NOT DEFINED ${LUA_INCLUDES})
			set(LUA_INCLUDES /usr/include/lua5.3)
		endif()
	elseif(${LUA_VERSION} EQUAL 52)
		target_link_libraries(sgfx lua5.2)
		add_definitions(-DLUA_5_3)
		if(NOT DEFINED ${LUA_INCLUDES})
			set(LUA_INCLUDES /usr/include/lua5.2)
		endif()
	elseif(${LUA_VERSION} EQUAL 51)
		target_link_libraries(sgfx lua5.1)
		add_definitions(-DLUA_5_1)
		if(NOT DEFINED ${LUA_INCLUDES})
			set(LUA_INCLUDES /usr/include/lua5.1)
		endif()
	endif()
endif()

target_include_directories (sgfx PUBLIC
		${PROJECT_SOURCE_DIR}/includes/core
		${PROJECT_SOURCE_DIR}/includes/utils
if(${LUA_SUPPORT})
		${LUA_INCLUDES}
endif()
	)

set_target_properties(sgfx PROPERTIES 
					VERSION ${SGFX_VERSION_STRING} 
					SOVERSION ${SGFX_VERSION_MAJOR} 
					DESCRIPTION ${SGFX_DESCRIPTION} 
					)

if(CMAKE_STRIP)
	add_custom_command( TARGET sgfx POST_BUILD COMMAND ${CMAKE_STRIP} -s *${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()

add_custom_target(link_target ALL
					COMMAND ${CMAKE_COMMAND} -E create_symlink "libsgfx.so" "sgfx.so")