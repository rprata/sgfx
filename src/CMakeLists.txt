add_library (ibutterfree SHARED
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
