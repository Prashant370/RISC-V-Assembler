# RISCV Assembler

**Conversion of Assembly code to Machine code**

The following project is a course project under the guidance of [Dr T.V Kalyan](https://sites.google.com/view/kalyantv). It is an Assembler written in c++ which converts the `Assembly code` written in `RISCV syntax` to `Machine code`.

## Valid Instructions

### R format:
- add
- and
- or
- sll
- slt
- sra
- srl
- sub
- xor
- mul
- div
- rem

### I format:
- addi
- andi
- ori
- lb
- ld
- lh
- lw
- jalr

### S format:
- sb
- sw
- sd
- sh

### SB format:
- beq
- bne
- bge
- blt

### U format:
- auipc
- lui

### UJ format:
- jal

### Assembler Directives:
- .text
- .data
- .byte
- .half
- .word
- .dword
- .asciiz

## Team Members
| Name                     | Entry Number |
|--------------------------| -------------|
| [Pranav Dipesh Bhole](https://github.com/pranavbhole123) | 2022CSB1103  |
| [Prashant Kumar](https://github.com/Prashant370)            | 2022CSB1202  |
| [Kartikey Sahu](https://github.com/kartikeysahu987)          | 2022CSB1087  |

## Technology Stack
1. C++
2. Assembly Language (RISC V ISA)

**advanced_tests** contains files required to convert `Assembly Code` written in `RISC V` syntax into `Machine Code`.  
**.asm file**: These are the actual files that need to be converted into `Machine Code`.  
**.mc file**: This is the machine code file after conversion.

## General Instructions To Run Locally

1. If you do not have the code for this RISC-V assembler, clone the repository and checkout the code:
    ```bash
    git clone URL
    ```

2. Compile the `main1.cpp` file using gcc:
    ```bash
    g++ main1.cpp
    ```

3. Run the executable:
    ```bash
    ./a.out
    ```

4. Another file named `comment_free_test_file.asm` will be created from `test_file.asm`.

5. You are ready with machine code in `output.mc` file, which includes the memory segment as well.


# Screenshots
### Input Assembly Code Looks like 
![input](https://github.com/Prashant370/RISC-V-Assembler/assets/100296448/5a8e4a4f-e612-4d8b-821e-401e8293543f)
### Output Expected Machine Code
![output](https://github.com/Prashant370/RISC-V-Assembler/assets/100296448/09f512db-f8bb-45f9-9f2c-97afc1b20d2a)
### Memory Segment Looks Like
![mem](https://github.com/Prashant370/RISC-V-Assembler/assets/100296448/9d22f46d-6261-4918-b76f-058d83ea5d36)

 
