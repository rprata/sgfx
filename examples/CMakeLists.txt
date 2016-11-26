add_executable (helloworld helloworld.c)
add_executable (drawline drawline.c)
add_executable (drawcircle drawcircle.c)

target_link_libraries (helloworld LINK_PUBLIC ibutterfree)
target_link_libraries (drawline LINK_PUBLIC ibutterfree)
target_link_libraries (drawcircle LINK_PUBLIC ibutterfree)