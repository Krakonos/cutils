/******************************************************************************
 * Filename: htable_test.c
 * Description:
 *
 * Version: 1.0
 * Created: Nov 14 2009 23:51:38
 * Last modified: Nov 14 2009 23:51:38
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#include <config.h>
#include <string.h>

#include "htable.c"
#include "test.h"

#define TEST_SIZE 513

int removed;

void destroy(void *key, void *data) {
	free(key);
	free(data);
	removed++;
}

int main(int argc, char **argv) {
	htable_t *table = htable_init(0);
	table->func_destruct = &destroy;

	int globbad = 0;

	TBEGIN("hashtable insertion & search");
	for (int i = 0; i < TEST_SIZE; i++) {
		char *key, *value;
		key = malloc(sizeof(char)*128);
		snprintf(key, 128, "%i", i);
		value = strdup(key);
		htable_insert(table, key, value);
	}
/*	htable_debug_print(table); */

	int good = 0;

	/* Search for all values */
	for (int i = 0; i < TEST_SIZE; i++) {
		char key[128];
		snprintf(key, 128, "%i", i);
		char *value = htable_search( table, key );
		if (value != NULL)
		if (strcmp(key, value) == 0) good++;
	}
	TEST(good == TEST_SIZE,globbad++);

	TBEGIN("selective removal");
	good = 0;
	/* Delete & search for all values */
	for (int i = 0; i < TEST_SIZE; i++) {
		char key[128];
		snprintf(key, 128, "%i", i);
		htable_remove( table, key );
		char *value = htable_search( table, key );
		if (value == NULL) good++;
	}
	TEST(good == TEST_SIZE,globbad++);
	htable_destroy(table);
	
	/* Test autoremove */
	table = htable_init(0);
	removed = 0;
	TBEGIN("autoremove");
	table->func_destruct = &destroy;
	for (int i = 0; i < TEST_SIZE; i++) {
		char *key, *value;
		key = malloc(sizeof(char)*128);
		snprintf(key, 128, "%i", i);
		value = strdup(key);
		htable_insert(table, key, value);
	}
	htable_destroy(table);
	TEST(removed == TEST_SIZE,globbad++);

	return globbad;
}

// vim:sw=4:ts=4
