#include "ibutterfree_event.h"

#ifdef __POSIX__
static bool event_th_running = true;
static pthread_t event_th;
void * event_func_th(void * args) 
{
	while(event_th_running) 
	{
		IButterFreeTouchStruct bfts;
		if (ibutterfree_event_read(&bfts) == IBUTTERFREE_OK) 
		{
			m_bfevs->cb(bfts);
		}
	}
	event_th_running = false;
	return NULL;
}
#endif		

static int x_factor = 1, y_factor = 1;

IBUTTERFREE_RET ibutterfree_event_init(IButterFreeSurface * surface)
{
	if (!m_bfevs)
	{
		int xres, yres;
		ibutterfree_get_resolution(surface, &xres, &yres);
		x_factor = (X_MAX - X_MIN)/xres;
		y_factor = (Y_MAX - Y_MIN)/yres;

		m_bfevs = (IButterFreeEventInternalStruct *) malloc(sizeof(IButterFreeEventInternalStruct));
		m_bfevs->evfd = open(ibutterfree_get_fdev(), O_RDONLY);
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("ibutterfree_event_init already initialized");
		return IBUTTERFREE_ERROR;
	}
}

void ibutterfree_event_callback_register(IButterFreeSurface * surface, event_cb_t event_cb) {
	if (m_bfevs) {
		m_bfevs->cb = event_cb;
#ifdef __POSIX__
	event_th_running = true;
 	if(pthread_create(&event_th, NULL, event_func_th, NULL)) 
 	{
 		event_th_running = false;
		IBUTTERFREE_LOG_ERROR("Cannot create pthread");
	}		
#endif		
	} else {
		IBUTTERFREE_LOG_ERROR("Cannot register event callback");
	}
}

IBUTTERFREE_RET ibutterfree_event_read(IButterFreeTouchStruct * bfts)
{	
	int counter_x = 0, counter_y = 0, counter_pressure = 0;
	int sum_x = 0, sum_y = 0, sum_pressure = 0;
	if (m_bfevs)
	{
		bfts->pressure = -1;
		while (true)
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
#ifdef __POSIX__
		if (m_bfevs->cb && event_th_running)
		{
			event_th_running = false;
			pthread_join(event_th, NULL);
		}
#endif
		free(m_bfevs);
		m_bfevs = NULL;
	}
}