#include "ibutterfree_config.h"

void ibutterfree_config_read(void)
{
	FILE * fp;
	char buff[1024];

	if (!m_bfcs)
	{
		m_bfcs = (IButterFreeConfigStruct *) malloc(sizeof(IButterFreeConfigStruct));
		strncpy(m_bfcs->fdfb, FB, strlen(FB));
		strncpy(m_bfcs->fdev, INPUT, strlen(INPUT));
	}

	fp = fopen(CONFIG, "r");
	if(fp != NULL)
	{
		while(!feof(fp))
		{
			if(fgets(buff, 1024, fp) != NULL)
			{
				if (strstr(buff, "FDFB") != NULL)
				{
					strncpy(m_bfcs->fdfb, buff + 5, strlen(buff + 5) - 1);
					*(m_bfcs->fdfb + strlen(buff + 5) - 1) = '\0';
					IBUTTERFREE_LOG_TRACK("fdfb: %s", m_bfcs->fdfb);
				}
				else if (strstr(buff, "FDEV") != NULL)
				{
					strncpy(m_bfcs->fdev, buff + 5, strlen(buff + 5) - 1);
					*(m_bfcs->fdev + strlen(buff + 5) - 1) = '\0';
					IBUTTERFREE_LOG_TRACK("fdev: %s", m_bfcs->fdev);
				}
			}

	    }
	} 
	else 
	{
	    IBUTTERFREE_LOG_ERROR("Couldn't open file");
		ibutterfree_set_message_error("Couldn't open file");
	}
}

const char * ibutterfree_get_fdfb(void)
{
	if (m_bfcs)
		return m_bfcs->fdfb;
	else
		return NULL;
}

const char * ibutterfree_get_fdev(void)
{
	if (m_bfcs)
		return m_bfcs->fdev;
	else
		return NULL;
}