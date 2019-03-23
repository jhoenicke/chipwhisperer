TREZOR ecdsa test routines
==========================

INSTALL
-------

You need to link trezor-crypto and libopencm3 from trezor-mcu/vendor
to this directory.  Make sure you have a gcc-arm in your path. Then
build with

    make PLATFORM=CW308_STM32F2 CRYPTO_TARGET=TINYAES128C

We currently use a mixture of libopencm3 and stm32 HAL, but it just
works.

Flash with:

    openocd -f interface/stlink-v2.cfg -c "transport select hla_swd" -f target/stm32f2x.cfg  -c "init; reset halt; flash write_image erase simpleserial-ecdsa-CW308_STM32F2.hex ;exit"