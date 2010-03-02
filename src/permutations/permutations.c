/******************************************************************************
 * Filename: permutations.c
 * Description: operations with permutations
 *
 * Version: 1.0
 * Created: Mar 02 2010 19:51:21
 * Last modified: Mar 02 2010 19:51:21
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include <assert.h>

void swap( int *perm, int a, int b ) {
	int tmp = perm[a];
	perm[a] = perm[b];
	perm[b] = tmp;
}

void reverse(int *perm, int length) {
	int first = 0;
	int last = length-1;
	while ( first < last) swap(perm, first++, last--);
}

int next_permutation(int *perm, int length) {
	/*
	 * Implements algorithm to generate next lexographical permutation,
	 * like described for example here: 
	 *	 http://wordaligned.org/articles/next-permutation \
	 */
	
	assert(perm);
	assert(length > 0);

	/* FIXME: Why 2? */
	if (length <= 2) return 0;

	/* Get largetst decreasing tail */
	int last = length-1;
	while ((perm[last-1] >= perm[last]) && (last > 0)) 
		last--;
	
	/* If permutation is whole decreasing */
	if (last == 0) {
		reverse(perm, length);
		return 0;
	}

	/* Find first greater element than head */
	int h = last-1;
	int i = length-1;
	while ((i > h) && (perm[i] < perm[h])) i--;
	swap(perm, i, h);
	reverse(perm+last, length-last);
	return 1;
}
