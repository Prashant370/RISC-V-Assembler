    .text
##
# MERGESORT(*testArray, first, last)
# param a0 -> first element address
# param a1 -> last element address
##
mergesort:

# Stack management
    addi  sp, sp, -32            # Adjust stack pointer
    sd    ra, 0 (sp)             # Load return address
    sd    a0, 8 (sp)             # Load first element address
    sd    a1, 16 (sp)            # Load last element address


# Base case
# li t1, 1 # Size of one element ---> Pseudo Instructions
    sub   t0, a1, a0             # Calculate number of elements
   # ble   t0, t1, mergesort_end  # If only one element remains in the array, return

    #srli  t0, t0, 1              # Divide array size to get half of the element
    add   a1, a0, t0             # Calculate array midpoint address
    sd    a1, 24 (sp)            # Store it on the stack

    jal   x0 mergesort              # Recursive call on first half of the array

    ld    a0, 24 (sp)            # Load midpoint back from the stack
    ld    a1, 16 (sp)            # Load last element address back from the stack

    jal   x0 mergesort              # Recursive call on second half of the array

    ld    a0, 8 (sp)             # Load first element address back from the stack
    ld    a1, 24 (sp)            # Load midpoint address back form the stack
    ld    a2, 16 (sp)            # Load last element address back from the stack

    jal   x0 merge                  # Merge two sorted sub-arrays

mergesort_end:
    ld    ra, 0 (sp)
    addi  sp, sp, 32
# ret ---> Pseudo Instructions

##
# Merge(*testArray, first, midpoint, last)
# param a0 -> first address of first array
# param a1 -> first address of second array
# param a2 -> last address of second array
##
merge:

# Stack management
    addi  sp, sp, -32            # Adjust stack pointer
    sd    ra, 0 (sp)             # Load return address
    sd    a0, 8 (sp)             # Load first element of first array address
    sd    a1, 16 (sp)            # Load first element of second array address
    sd    a2, 24 (sp)            # Load last element of second array address

    add   s0, x0 a0              # First half address copy
    add   s1, x0 a1              # Second half address copy

merge_loop:

    add   t0, x0 s0              # copy first half position address
    add   t1, x0 s1              # copy second half position address
    lb    t0, 0 (t0)             # Load first half position value
    lb    t1, 0 (t1)             # Load second half position value

    #bgt   t1, t0, shift_skip     # If lower value is first, no need to perform operations

    add   a0, x0 s1              # a0 -> element to move
    add   a1, x0 s0              # a1 -> address to move it to
    jal   x0 shift                  # jump to shift

    addi  s1, s1, 1

shift_skip:

    addi  s0, s0, 1              # Increment first half index and point to the next element
#ld a2, 24 (sp) # Load back last element address ---> Pseudo Instructions

    bge   s0, a2, merge_loop_end
    bge   s1, a2, merge_loop_end
    beq   x0, x0, merge_loop

##
# Shift array element to a lower address
# param a0 -> address of element to shift
# param a1 -> address of where to move a0
##
shift:

    #ble   a0, a1, shift_end      # Location reached, stop shifting
    addi  t3, a0, -1             # Go to the previous element in the array
    lb    t4, 0 (a0)             # Get current element pointer
    lb    t5, 0 (t3)             # Get previous element pointer
    sb    t4, 0 (t3)             # Copy current element pointer to previous element address
    sb    t5, 0 (a0)             # Copy previous element pointer to current element address
    addi  a0, x0 3              # Shift current position back
    beq   x0, x0, shift          # Loop again

shift_end:

merge_loop_end:

# ld ra, 0 (sp) -->pseudo instructions that's why I comment it
    addi  sp, sp, 32
#ret ---> Pseudo Instructions