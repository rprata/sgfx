#include "ibutterfree.h"

IBUTTERFREE_RET ibutterfree_init(int argc, char ** argv)
{
    if (!m_bfs)
    {
    	m_bfs = (IButterFreeStruct *)malloc(sizeof(IButterFreeStruct));
    	m_bfs->fbfd = 0;
        m_bfs->screensize = 0;
        m_bfs->fbp = NULL;

    	m_bfs->fbfd = open(FB, O_RDWR);
        if (m_bfs->fbfd == -1)
        {
            IBUTTERFREE_LOG_ERROR("Cannot open framebuffer device");
            return IBUTTERFREE_ERROR;
        }

        if (ioctl(m_bfs->fbfd, FBIOGET_FSCREENINFO, &m_bfs->finfo) == -1) 
        {
            IBUTTERFREE_LOG_ERROR("Reading fixed information");
            return IBUTTERFREE_ERROR;
        }

        if (ioctl(m_bfs->fbfd, FBIOGET_VSCREENINFO, &m_bfs->vinfo) == -1) 
        {
            IBUTTERFREE_LOG_ERROR("Reading variable information");
            return IBUTTERFREE_ERROR;
        }

        m_bfs->screensize = m_bfs->vinfo.xres_virtual * m_bfs->vinfo.yres_virtual * (m_bfs->vinfo.bits_per_pixel / 8);

        m_bfs->fbp = (char *) mmap(0, m_bfs->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, m_bfs->fbfd, (off_t) 0);
  		m_bfs->bbp = (char *) mmap(0, m_bfs->screensize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);
        
        if (!m_bfs->fbp && !m_bfs->bbp) 
        {
            IBUTTERFREE_LOG_ERROR("Failed to map framebuffer device to memory");
            return IBUTTERFREE_ERROR;
        }

        memset(m_bfs->fbp, 0xFF, m_bfs->screensize);
    	memset(m_bfs->bbp, 0xFF, m_bfs->screensize);
    }

	return IBUTTERFREE_OK;
}

void ibutterfree_close(void)
{
    if (m_bfs) 
    {
    	munmap(m_bfs->fbp, m_bfs->screensize);
    	munmap(m_bfs->bbp, m_bfs->screensize);
    	close(m_bfs->fbfd);
        free(m_bfs);
        m_bfs = NULL;
    }
}