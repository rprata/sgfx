#include "ibutterfree.h"

IBUTTERFREE_RET ibutterfree_init(int argc, char ** argv)
{
	m_bfs = (IButterFreeStruct *)malloc(sizeof(IButterFreeStruct));
	m_bfs->fbfd = 0;
    m_bfs->screensize = 0;
    m_bfs->fbp = NULL;

	m_bfs->fbfd = open(FB, O_RDWR);
    if (m_bfs->fbfd == -1)
    {
        perror("Error: cannot open framebuffer device");
        return IBUTTERFREE_ERROR;
    }

    if (ioctl(m_bfs->fbfd, FBIOGET_FSCREENINFO, &m_bfs->finfo) == -1) 
    {
        perror("Error: reading fixed information");
        return IBUTTERFREE_ERROR;
    }

    if (ioctl(m_bfs->fbfd, FBIOGET_VSCREENINFO, &m_bfs->vinfo) == -1) 
    {
        perror("Error: reading variable information");
        return IBUTTERFREE_ERROR;
    }

    m_bfs->screensize = m_bfs->vinfo.xres * m_bfs->vinfo.yres * m_bfs->vinfo.bits_per_pixel / 8;

    m_bfs->fbp = (char *) mmap(0, m_bfs->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, m_bfs->fbfd, 0);
    if (m_bfs->fbp == NULL) 
    {
        perror("Error: failed to map framebuffer device to memory");
        return IBUTTERFREE_ERROR;
    }

	return IBUTTERFREE_OK;
}

void ibutterfree_close(void)
{
	free(m_bfs);
	m_bfs = NULL;
	close(m_bfs->fbfd);
}


IBUTTERFREE_RET ibutterfree_create_bf(IButterFreeStruct * bfs)
{
	if (m_bfs == NULL) 
	{
		perror("Error: failed to create bf");
		return IBUTTERFREE_ERROR;
	}
	memcpy(bfs, m_bfs, sizeof(IButterFreeStruct));
	return IBUTTERFREE_OK;
}