add_library (ibutterfree SHARED
		utils/ibutterfree_upng.c
		core/ibutterfree.c
		core/ibutterfree_surface.c
		core/ibutterfree_draw.c
		core/ibutterfree_image.c		
		)

set(CMAKE_C_FLAGS "-Wall -Werror -O3")

target_include_directories (ibutterfree PUBLIC
		${PROJECT_SOURCE_DIR}/includes/core
		${PROJECT_SOURCE_DIR}/includes/utils
		)

if(CMAKE_STRIP)
	add_custom_command( TARGET ibutterfree POST_BUILD COMMAND ${CMAKE_STRIP} -s *${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()