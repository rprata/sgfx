#ifndef __IBUTTERFREE_H__
#define __IBUTTERFREE_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define FB "/dev/fb0"

enum IBUTTERFREE_RET {
	IBUTTERFREE_ERROR,
	IBUTTERFREE_OK,
};

typedef struct IButterFreeStruct_ST {
	int fbfd;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize;
	char *fbp;
} IButterFreeStruct;

IButterFreeStruct * m_bfs;

IBUTTERFREE_RET ibutterfree_init(int argc, char ** argv);
void ibutterfree_close(void);
IBUTTERFREE_RET ibutterfree_create_bf(IButterFreeStruct * bfs);

#endif