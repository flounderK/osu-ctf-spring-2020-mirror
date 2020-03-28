#!/bin/bash

qemu-riscv64 -E LD_PRELOAD=/usr/riscv64-linux-gnu/lib/libc.so.6 ./crackme02 < admin
