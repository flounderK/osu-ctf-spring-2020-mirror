#!/usr/bin/env python3
import socket
import os

byte_range = list(range(16*16))
max_input_bytes = 10


with open(str(max_input_bytes) + '_bytes.txt','wb') as fp:
    counter = 0
    while True:
        fp.write(counter.to_bytes(max_input_bytes, 'little'))
        fp.write(b'\n')
        counter += 1
        

