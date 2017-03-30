#include "ibutterfree_event.h"

// void ibutterfree_event_callback_register(event_cb_t cb, void * data)
// {
//     saved.cb = cb;
//     saved.data = data;
// }

static int x_factor = 1, y_factor = 1;

IBUTTERFREE_RET ibutterfree_event_init(IButterFreeSurface * surface)
{
	if (!m_bfevs)
	{
		int xres, yres;
		ibutterfree_get_resolution(surface, &xres, &yres);
		x_factor = (X_MAX - X_MIN)/xres;
		y_factor = (Y_MAX - Y_MIN)/yres;

		m_bfevs = (IButterFreeEventStruct *) malloc(sizeof(IButterFreeEventStruct));
		m_bfevs->evfd = open(INPUT, O_RDONLY);
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Cannot use IButterFreeEventStruct");
		return IBUTTERFREE_ERROR;
	}
}

IBUTTERFREE_RET ibutterfree_event_read(IButterFreeTouchStruct * bfts)
{	
	int counter_x = 0, counter_y = 0, counter_pressure = 0;
	int sum_x = 0, sum_y = 0, sum_pressure = 0;
	if (m_bfevs)
	{
		bfts->pressure = -1;
		while (1)
		{
			if (read(m_bfevs->evfd, &m_bfevs->ev, sizeof(struct input_event)) != -1)
			{
		        if(m_bfevs->ev.type == EV_ABS)
		        {
		            if (m_bfevs->ev.code == ABS_X)
		            {
		            	sum_x += m_bfevs->ev.value/x_factor;
		            	counter_x++;
		            }
		            if (m_bfevs->ev.code == ABS_Y)
		            {
		                sum_y += m_bfevs->ev.value/y_factor;
		                counter_y++;
		            }
		            if(m_bfevs->ev.code == ABS_PRESSURE)
		            {
		            	if (m_bfevs->ev.value == 0)	
		            		break;
		                sum_pressure += m_bfevs->ev.value;
		                counter_pressure++;
		            }
		        }
		        bfts->pressed = 1;
		    }
	    }
	    bfts->x_abs = sum_x / counter_x;
	    bfts->y_abs = sum_y / counter_y;
	    bfts->pressure = sum_pressure / counter_pressure;
	    bfts->pressed = 0;
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Cannot use ibutterfree_event_read()");
		return IBUTTERFREE_ERROR;
	}
}

void ibutterfree_event_destroy(void)
{
	if (m_bfevs)
	{
		close(m_bfevs->evfd);
		free(m_bfevs);
		m_bfevs = NULL;
	}
}