    .data
string: 
    .asciiz "abcdefghgfedcba"

    .text
    addi    x1, x0, 1
    jal     x14, procedure

    beq     x0, x0, pp

procedure:
#palindrome code
#i and length-i are the respective indices till i < length-1
# to determine lenght
    addi    x5, x1, 0

loop:
    lb      x6, 0 (x1)
    beq     x6, x0, exit
    addi    x4, x4, 1
    addi    x1, x1, 1
    jal     x0   loop
exit:

#got the length now continue
    addi    x7, x4, -1          ##len-1
    add     x1, x5, x0          #reinitializing the adress in x1
loopya:
    bge     x6, x7, ex

    add     x8, x6, x1
    add     x9, x7, x1

    lb      x10, 0 ( x8)
    lb      x11, 0 (x9)
    beq     x10 x11, continue
    addi    x12 x0, -1         ##this will contain the answer
    jalr    x13, x14, 0

continue:
    addi    x6, x6, 1
    addi    x7, x7, -1
    jal      x0      loopya

ex:
    addi    x12, x0, 1
    jalr    x13, x14, 0

pp: