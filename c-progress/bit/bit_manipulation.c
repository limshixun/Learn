#include "bit_manipulation.h"
#include <stdio.h>

/*
 * N = 111, K = 1, Operator | (OR)
 * bitmask = 001 = (1 < 0) = (1 < K - 1)
 *    111
 * OR 001
 *    111
 */
int set_bit(int N, int K) { return N | (1 << (K - 1)); }

/*
 * N = 111, K = 1, Operator & (AND)
 * bitmask = 110 = NOT(001) = ~(1 < K - 1)
 *     111
 * AND 110
 *     110
 */
int clear_bit(int N, int K) { return N & ~(1 << (K - 1)); }

/*
 * N = 111, K = 1, Operator ^ (XOR)
 * bitmask = 001 = (1 < K - 1)
 *     111  |      110
 * XOR 001  |  XOR 001
 *     110  |      111
 */
int toggle_bit(int N, int K) { return N ^ (1 << (K - 1)); }
