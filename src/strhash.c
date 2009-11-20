/******************************************************************************
 * Filename: strhash.c
 * Description:
 *
 * Version: 1.0
 * Created: Nov 13 2009 11:17:47
 * Last modified: Nov 13 2009 11:17:47
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include "strhash.h"

/* 
 * djb2 hashing function
 *
 * http://www.cse.yorku.ca/~oz/hash.html
 */

unsigned long strhash( char *str ) {
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

// vim:sw=4:ts=4
