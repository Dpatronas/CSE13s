//sieves the vector
#include "sieve.h"
#include "bv.h"
#include <math.h>

//From lab manual assignment 4
//The Sieve of Eratothenes
void sieve(BitVector *v) {
	bv_set_all_bits(v);
	bv_clr_bit(v,0);
	bv_clr_bit(v,1);
	bv_set_bit(v,2);
	for (uint32_t i = 2; i < sqrt(bv_get_len(v)); i++ ) {
		//Prime means bit is set
		if (bv_get_bit(v,i)) {
			for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
				bv_clr_bit(v, (k + i) * i);
			}
		}
	}
	return;
}
