#include "ibutterfree_log.h"

void ibutterfree_set_msg_level(IBUTTERFREE_MSG_LEVEL msg_level)
{
	m_msg_level = msg_level;
}

void ibutterfree_log(IBUTTERFREE_MSG_LEVEL msg_level_msg, const char * fmt, ...)
{
	if (msg_level_msg > IBUTTERFREE_MSG_LEVEL_NONE && msg_level_msg < m_msg_level) 
	{
		char buffer[4096];
		va_list args;
	    va_start(args, fmt);
	    vsnprintf(buffer, sizeof(buffer), fmt, args);
	    switch (msg_level_msg) {
	    	case IBUTTERFREE_MSG_LEVEL_TRACK:
	    		printf(ANSI_COLOR_CYAN "[TRACK][%s - %s:%d] %s" ANSI_COLOR_CYAN "\n", __func__, __FILE__, __LINE__, buffer);
	    		break;
	    	case IBUTTERFREE_MSG_LEVEL_DEBUG:
	    		printf(ANSI_COLOR_BLUE "[DEBUG][%s - %s:%d] %s" ANSI_COLOR_BLUE "\n", __func__, __FILE__, __LINE__, buffer);
	    		break;
	    	case IBUTTERFREE_MSG_LEVEL_ALERT:
	    		printf(ANSI_COLOR_GREEN "[ALERT][%s - %s:%d] %s" ANSI_COLOR_GREEN "\n", __func__, __FILE__, __LINE__, buffer);
	    		break;
	    	case IBUTTERFREE_MSG_LEVEL_WARNING:
	    		printf(ANSI_COLOR_MAGENTA "[WARNING][%s - %s:%d] %s" ANSI_COLOR_MAGENTA "\n", __func__, __FILE__, __LINE__, buffer);
	    		break;
	    	case IBUTTERFREE_MSG_LEVEL_ERROR:
	    		printf(ANSI_COLOR_RED "[ERROR][%s - %s:%d] %s" ANSI_COLOR_RED "\n", __func__, __FILE__, __LINE__, buffer);
	    		break;	    	
	    	default:
	    		break;

	    };
	    va_end(args);
	}
}
