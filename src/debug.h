/******************************************************************************
 * Filename: debug.h
 * Description: debugging macros collection
 *
 * Version: 1.0
 * Created: Oct 10 2009 17:55:11
 * Last modified: Oct 13 2009 03:53:05 PM
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <config.h>

#ifdef DEBUG
#include <stdio.h>
#define debug(msg) fprintf(stderr, "(Debug): %s\n", msg)
#define debugf(fmt,...) fprintf(stderr, "(Debug): " fmt "\n", __VA_ARGS__)
#else
#define debug(msg)
#define debugf(fmt,...) ;
#endif

#define warn(msg) fprintf(stderr, "(Warning): %s\n", msg)
#define warnf(fmt,...) fprintf(stderr, "(Warning): " fmt "\n", __VA_ARGS__)

#endif
// vim:sw=4:ts=4
