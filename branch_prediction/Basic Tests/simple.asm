core   0: 0x8000c81c (0x00150513) addi    a0, a0, 1
core   0: 0x8000c820 (0xfff5c703) lbu     a4, -1(a1)
core   0: 0x8000c824 (0x00078863) beqz    a5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     a5, a4, pc - 20
core   0: 0x8000c814 (0x00054783) lbu     a5, 0(a0)
core   0: 0x8000c818 (0x00158593) addi    a1, a1, 1
core   0: 0x8000c81c (0x00150513) addi    a0, a0, 1
core   0: 0x8000c820 (0xfff5c703) lbu     a4, -1(a1)
core   0: 0x8000c824 (0x00078863) beqz    a5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     a5, a4, pc - 20
core   0: 0x8000c82c (0x40e78533) sub     a0, a5, a4
core   0: 0x8000c830 (0x00008067) ret
core   0: 0x80005b98 (0x02051663) bnez    a0, pc + 44
core   0: 0x80005bc4 (0x003c0c13) addi    s8, s8, 3
core   0: 0x80005bc8 (0x41fc5793) srai    a5, s8, 31
core   0: 0x80005bcc (0x0037f793) andi    a5, a5, 3
core   0: 0x80005bd0 (0x018787b3) add     a5, a5, s8
core   0: 0x80005bd4 (0x004b2703) lw      a4, 4(s6)