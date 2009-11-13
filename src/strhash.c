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

unsigned int strhash( char *string ) {
	unsigned int hash = 0;
	int i = 0;
	while (string[i] != 0 ) {
		hash = 41*(i + string[i]);
		i++;
	}

	return hash;
}

// vim:sw=4:ts=4
