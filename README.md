# RISCV Assembler
Conversion of Assembly code to Machine code


The following project is a course project under the guidance of [Dr T.V Kalyan](https://sites.google.com/view/kalyantv). It is Assembler which converts the `Assembly code` written `RISCV syntax` to `Machine code` .  

## Valid Instructions

**R format:**
add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem

**I format:**
addi, andi, ori, lb, ld, lh, lw, jalr

**S format:**
sb, sw, sd, sh

**SB format:**
beq, bne, bge, blt

**U format:**
auipc, lui

**UJ format:**
jal

**Assembler Directives:**
.text, .data, .byte, .half, .word, .dword, .asciiz

## Team Members
| Name            | Entry Number |
|:---------------:| -----------: |
| [Pranav Dipesh Bhole](https://github.com/pranavbhole123) | 2022CSB1103  |
| [Prashant Kumar](https://github.com/Prashant370)     | 2022CSB1202  |
| [Kartikey Sahu](https://github.com/kartikeysahu987)     | 2022CSB1087  |


## Technology Stack
1. C++
2. Assembly Language [Risc V ISA]



**advanced_tests** contains files required to convert `Assembly Code` written in `RISC V` syntax into `Machine Code`  
**.asm file** are actual one which is required to convert in `Machine Code`  
**.mc file** is the machine code file after conversion 



## General Instructions To Run Locally

1. If you do not have the code for this RISC-V assembler, clone the repository and checkout the code:
    ```bash
    git clone URL
    ```

2. Compile the main1.cpp file using gcc:
    ```bash
    gcc main1.cpp
    ```

3. Run the executable:
    ```bash
    ./a.out
    ```

4. Another file named "comment_free_test_file.asm" will be created from "test_file.asm".

5. You are ready with machine code in output.mc file having memory segment also.


