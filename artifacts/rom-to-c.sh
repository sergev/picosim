#!/bin/sh

set -x
arm-none-eabi-objcopy -O binary pico-bootrom-b2.elf pico-bootrom-b2.bin
xxd -i pico-bootrom-b2.bin | sed 's/^unsigned/const unsigned/' > pico-bootrom-b2.c
