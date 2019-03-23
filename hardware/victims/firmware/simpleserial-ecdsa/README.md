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