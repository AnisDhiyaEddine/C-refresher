/* ========================================================================= *
 * Z-Score interface
 * ========================================================================= */

#ifndef _Z_SCORE_H_
#define _Z_SCORE_H_

#include <stdint.h>
#include "BinarySearchTree.h"
#include "LinkedList.h"

/* ------------------------------------------------------------------------- *
 * Encode two geographical coordinates into their zscore.
 *
 * PARAMETERS
 * latitude         A double in [-90.0, 90.0]
 * longitutde       A double in [-180.0, 180.0]
 *
 * RETURN
 * code             A Z-score corresponding to the coordinate
 * ------------------------------------------------------------------------- */
uint64_t zEncode(double latitude, double longitutde);

BinarySearchTree *fillZbst(LinkedList *list, int comparison_fn_t(const void *, const void *));

#endif // _Z_SCORE_H_
