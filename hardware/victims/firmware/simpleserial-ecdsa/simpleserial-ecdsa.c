/*
    This file is part of the ChipWhisperer Example Targets
    Copyright (C) 2012-2017 NewAE Technology Inc.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "aes-independant.h"
#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <stdlib.h>
#include "ecdsa.h"
#include "secp256k1.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/rng.h>
#include "rng.h"

static bignum256 a1;
static curve_point base;

uint8_t set_base(uint8_t* k)
{
        bn_read_be(k, &a1);
	return 0x00;
}

uint8_t multiply(uint8_t* pt)
{
	bignum256 a;
	curve_point res;
	uint8_t pubkey[33];
        bn_read_be(pt, &a);
	scalar_multiply(secp256k1_info.params, &a1, &base);
	point_multiply(secp256k1_info.params, &a, &base, &res);
	pubkey[0] = 2 + (res.y.val[0] & 1);
	bn_write_be(&res.x, pubkey + 1);
	simpleserial_put('r', 32, pubkey + 1);
	return 0x00;
}

uint8_t set_random(uint8_t* seed)
{
	srand((uint32_t)(seed[0] << 24) + (seed[1] << 16) + (seed[2] << 8) + seed[3]);
	return 0;
}

uint8_t reset(uint8_t* x)
{
	// Reset key here if needed
	return 0x00;
}

int main(void)
{
#if 1
	struct rcc_clock_scale clock = rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_120MHZ];
	rcc_clock_setup_hse_3v3(&clock);

	// enable RNG
	rcc_periph_clock_enable(RCC_RNG);
	RNG_CR |= RNG_CR_RNGEN;
	// to be extra careful and heed the STM32F205xx Reference manual, Section 20.3.1
	// we don't use the first random number generated after setting the RNGEN bit in setup
	random32();

#else
    platform_init();
#endif
    init_uart();
    trigger_setup();

    /* Uncomment this to get a HELLO message for debug */

    putch('h');
    putch('e');
    putch('l');
    putch('l');
    putch('o');
    putch('\n');

	simpleserial_init();
    simpleserial_addcmd('k', 32, set_base);
    simpleserial_addcmd('p', 32, multiply);
    simpleserial_addcmd('r', 4, set_random);
    simpleserial_addcmd('x',  0,   reset);
    while(1) {
	simpleserial_get();
    }
}
