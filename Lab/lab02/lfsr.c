#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
		uint16_t bit0, bit2, bit3, bit5;
		uint16_t new_bit;
		bit0 = *reg & 1;
		bit2 = (*reg & 4) >> 2;
		bit3 = (*reg & 8) >> 3;
		bit5 = (*reg & 32) >> 5;
		new_bit = bit0 ^ bit2 ^ bit3 ^ bit5;
		new_bit = new_bit << 15;
		*reg = *reg >> 1;
		*reg = *reg | new_bit;
}

