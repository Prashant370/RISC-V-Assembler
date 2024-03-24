#q5 lab 4 
.data 
assingments: .byte 3, 4, 5, 3, 4, 5, 3  ## marks of 7 theory assingments out of 5
quizzes: .byte 7, 8, 9, 7, 8, 9, 7  #marks of 7 quizzes
lab: .byte 3, 4, 5, 3
labtest: .byte 10, 9
labproject: .byte 10
midsem: .byte 25
endsem: .byte 25
address: .word 0x10000018

.text
addi x1, x0, 1

proc4_best:

jal x9, bubble_sort
#let us store answers in x4,5,6,7

addi x2, x2, -4
lb x4, 3  (x1)
sb x4, 0 (x2)

lb x5, 4 (x1)
sb x5, 1 (x2)

lb x6, 5 (x1)
sb x6, 2 (x2)

lb x7, 6 (x1)
sb x7, 3 (x2)




proc5_best:

jal x9 bubble_sort

#let us store answers in x4,5,6,7,8
addi x2, x2, -5

lb x8, 2 (x1)
sb x8, 0 (x2)

lb x4, 3 (x1)
sb x4, 1 (x2)

lb x5, 4 (x1)
sb x5, 2 (x2)

lb x6, 5 (x1)
sb x6, 3 (x2)

lb x7, 6 (x1)
sb x7, 4 (x2)

beq x0, x0, pp   #succesfuuly got the values strored in stack

bubble_sort:
# let x3 be outer loop index
#let x4 be inner loop index
#let x5 contain the lenght
#let x1 contain base address




addi x2, x2, -4
sw x1, 0 (x2)
outrloop:
bge x3, x5, exit
addi x3, x3, 1
addi x4, x0, 0
lw x1, 0 (x2)
innerloop:
bge x4, x5, exit_inner
#wite here the swapping mechanism
lb x6, 0 (x1)
lb x7, 1 (x1)
 #incrementing the base adress
addi x4, x4, 1
blt x6, x7, continue
#let x8 be the temp register
addi x8, x6, 0
addi x6, x7, 0
addi x7, x8, 0
#swap the values in memory
sb x6, 0 (x1)
sb x7, 1 (x1)


continue:
addi x1, x1, 1
jal x0 innerloop
exit_inner:
jal x0 outrloop
exit: 
addi x2, x2, 4
pp:
