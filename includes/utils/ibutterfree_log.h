#ifndef __IBUTTERFREE_LOG_H__
#define __IBUTTERFREE_LOG_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

typedef enum IBUTTERFREE_MSG_LEVEL {
	IBUTTERFREE_MSG_LEVEL_NONE = -1,
	IBUTTERFREE_MSG_LEVEL_TRACK = 0,
	IBUTTERFREE_MSG_LEVEL_DEBUG = 1,
	IBUTTERFREE_MSG_LEVEL_ALERT = 2,
	IBUTTERFREE_MSG_LEVEL_WARNING = 4,
	IBUTTERFREE_MSG_LEVEL_ERROR = 5,
	IBUTTERFREE_MSG_LEVEL_ALL = 6
} IBUTTERFREE_MSG_LEVEL;

#ifndef IBUTTERFREE_DBG_MODE
	__attribute__((unused)) static IBUTTERFREE_MSG_LEVEL m_msg_level = IBUTTERFREE_MSG_LEVEL_NONE;
#else
	__attribute__((unused)) static IBUTTERFREE_MSG_LEVEL m_msg_level = IBUTTERFREE_MSG_LEVEL_ALL;
#endif

void ibutterfree_set_msg_level(IBUTTERFREE_MSG_LEVEL msg_level);
void ibutterfree_log(IBUTTERFREE_MSG_LEVEL msg_level_msg, const char *fmt, ...);

#endif