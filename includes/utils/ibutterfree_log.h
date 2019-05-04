/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms			*
 * of the MIT license. See the LICENSE file for details.					*
 ****************************************************************************/

/**
 * @file ibutterfree_log.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing log functions of IButterFree Library.
 *
 * File containing log functions of IButterFree Library.
 * IButterFree has the possibility to enable log levels and
 * is it possible to use log in library or in your application.
 * You can configure it using MACRO: IBUTTERFREE_MSG_LEVEL (by
 * default this value is IBUTTERFREE_MSG_LEVEL_NONE).
 */

#ifndef __IBUTTERFREE_LOG_H__
#define __IBUTTERFREE_LOG_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


const char * ibutterfree_get_message_error();

void ibutterfree_set_message_error(const char * msg);

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#define PRINTFUNCTION(format, ...) printf(format, __VA_ARGS__)
#define NEWLINE "\n"

#define LOG_FMT			"[%s][%s - %s:%d]"
#define LOG_ARGS(LEVEL)	LEVEL, __FUNCTION__, __FILE__, __LINE__

/**
 * @def IBUTTERFREE_MSG_LEVEL_NONE
 * @hideinitializer
 * @brief Disable all log messages.
 */
#define	IBUTTERFREE_MSG_LEVEL_NONE	0

/**
 * @def IBUTTERFREE_MSG_LEVEL_TRACK
 * @hideinitializer
 * @brief Configure level message to track.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_TRACK	1

/**
 * @def IBUTTERFREE_MSG_LEVEL_DEBUG
 * @hideinitializer
 * @brief Configure level message to debug.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_DEBUG	2

/**
 * @def IBUTTERFREE_MSG_LEVEL_ALERT
 * @hideinitializer
 * @brief Configure level message to alert.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_ALERT	3

/**
 * @def IBUTTERFREE_MSG_LEVEL_WRN
 * @hideinitializer
 * @brief Configure level message to warning.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_WRN	4

/**
 * @def IBUTTERFREE_MSG_LEVEL_ERROR
 * @hideinitializer
 * @brief Configure level message to error.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_ERROR	5

/**
 * @def IBUTTERFREE_MSG_LEVEL_ALL
 * @hideinitializer
 * @brief Enable all log messages.
 */ 
#define	IBUTTERFREE_MSG_LEVEL_ALL	6

/**
 * @def IBUTTERFREE_MSG_LEVEL
 * @hideinitializer
 * @brief Configure the message level. You can set it in CMakeLists.txt
 */
#ifndef IBUTTERFREE_MSG_LEVEL
#define IBUTTERFREE_MSG_LEVEL IBUTTERFREE_MSG_LEVEL_NONE
#endif

/**
 * @def IBUTTERFREE_LOG_TRACK
 * @hideinitializer
 * @brief Print track message.
 */
#if IBUTTERFREE_MSG_LEVEL >= IBUTTERFREE_MSG_LEVEL_TRACK
#define IBUTTERFREE_LOG_TRACK(message, args...) \
	PRINTFUNCTION(ANSI_COLOR_CYAN LOG_FMT message ANSI_COLOR_CYAN NEWLINE, LOG_ARGS("TRACK"), ## args)
#else 
#define	IBUTTERFREE_LOG_TRACK(message, args...)		
#endif

/**
 * @def IBUTTERFREE_LOG_DEBUG
 * @hideinitializer
 * @brief Print debug message.
 */
#if IBUTTERFREE_MSG_LEVEL >= IBUTTERFREE_MSG_LEVEL_DEBUG
#define IBUTTERFREE_LOG_DEBUG(message, args...) \
	PRINTFUNCTION(ANSI_COLOR_BLUE LOG_FMT message ANSI_COLOR_BLUE NEWLINE, LOG_ARGS("DEBUG"), ## args)
#else 
#define IBUTTERFREE_LOG_DEBUG(message, args...)	
#endif

/**
 * @def IBUTTERFREE_LOG_ALERT
 * @hideinitializer
 * @brief Print alert message.
 */
#if IBUTTERFREE_MSG_LEVEL >= IBUTTERFREE_MSG_LEVEL_ALERT
#define IBUTTERFREE_LOG_ALERT(message, args...) \
	PRINTFUNCTION(ANSI_COLOR_GREEN LOG_FMT message ANSI_COLOR_GREEN NEWLINE, LOG_ARGS("ALERT"), ## args)
#else 
#define	IBUTTERFREE_LOG_ALERT(message, args...)	
#endif

/**
 * @def IBUTTERFREE_LOG_WARNING
 * @hideinitializer
 * @brief Print warning message.
 */
#if IBUTTERFREE_MSG_LEVEL >= IBUTTERFREE_MSG_LEVEL_WARNING
#define IBUTTERFREE_LOG_WARNING(message, args...) \
	PRINTFUNCTION(ANSI_COLOR_MAGENTA LOG_FMT message ANSI_COLOR_MAGENTA NEWLINE, LOG_ARGS("WARNING"), ## args)
#else 
#define IBUTTERFREE_LOG_WARNING(message, args...)	
#endif

/**
 * @def IBUTTERFREE_LOG_ERROR
 * @hideinitializer
 * @brief Print error message.
 */
#if (IBUTTERFREE_MSG_LEVEL >= IBUTTERFREE_MSG_LEVEL_ERROR)
#define IBUTTERFREE_LOG_ERROR(message, args...) \
	PRINTFUNCTION(ANSI_COLOR_RED LOG_FMT message ANSI_COLOR_RED NEWLINE, LOG_ARGS("ERROR"), ## args)
#else 
#define	IBUTTERFREE_LOG_ERROR(message, args...)	
#endif	

#endif