/******************************************************************************
 * Filename: test.h
 * Description:
 *
 * Version: 1.0
 * Created: Nov 01 2009 14:23:29
 * Last modified: Nov 01 2009 14:23:29
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>

#define TEST(var,...) if (var) printf("ok\n"); else { printf("FAILED\n"); __VA_ARGS__; }
#define TBEGIN(name) printf("Testing " name "... ");

#endif
// vim:sw=4:ts=4
