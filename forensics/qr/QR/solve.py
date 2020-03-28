#!/usr/bin/python3

import sys
import os


def print_code(filename):
    with open(filename, 'r') as f:
        c = f.read().splitlines()

    black = '\x1b[40m '
    white = '\x1b[107m '
    newlines = list()
    for line in c:
        newline = ''
        for i in line:
            if i == '1':
                newline += black
            elif i == '0':
                newline += white
        newlines.append(newline)

    print('\x1b[49m\n'.join(newlines) + '\x1b[49m')
    print('\x1b[49m\n')

os.system('tac key > newkey')
os.system('./chall encrypted.qr newkey decrypted.qr')
print_code('decrypted.qr')
#
# for i in range(1000):
#     if i % 2 == 0:
#         os.system('./chall a key b')
#         print_code("b")
#     else:
#         os.system('./chall b key a')
#         print_code("a")


