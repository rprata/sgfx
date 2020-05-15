add_executable (helloworld helloworld.c)
add_executable (drawprimitives drawprimitives.c)
add_executable (animationcircle animationcircle.c)
add_executable (drawimage drawimage.c)
add_executable (drawtext drawtext.c)
add_executable (eventexample eventexample.c)


add_definitions(-DSGFX_MSG_LEVEL=SGFX_MSG_LEVEL_ALL)

target_link_libraries (helloworld LINK_PUBLIC sgfx)
target_link_libraries (drawprimitives LINK_PUBLIC sgfx)
target_link_libraries (animationcircle LINK_PUBLIC sgfx)
target_link_libraries (drawimage LINK_PUBLIC sgfx)
target_link_libraries (drawtext LINK_PUBLIC sgfx)
target_link_libraries (eventexample LINK_PUBLIC sgfx)
