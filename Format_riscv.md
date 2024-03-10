| Instruction | Format | Opcode | Func3 | Func7   |
|-------------|--------|--------|-------|---------|
| add         | R      | 0110011| 000   | 0000000 |
| and         | R      | 0110011| 111   | 0100000 |
| or          | R      | 0110011| 110   | 0000000 |
| sll         | R      | 0110011| 001   | 0000000 |
| slt         | R      | 0110011| 010   | 0000000 |
| sra         | R      | 0110011| 101   | 0100000 |
| srl         | R      | 0110011| 101   | 0000000 |
| sub         | R      | 0110011| 000   | 0100000 |
| xor         | R      | 0110011| 100   | 0000000 |
| mul         | R      | 0110011|       |         |
| div         | R      | 0110011|       |         |
| rem         | R      | 0110011|       |         |
| addi        | I      | 0010011| 000   |         |
| andi        | I      | 0010011| 111   |         |
| ori         | I      | 0010011| 110   |         |
| lb          | I      | 0000011| 000   |         |
| ld          | I      | 0000011| 011   |         |
| lh          | I      | 0000011| 001   |         |
| lw          | I      | 0000011| 010   |         |
| jalr        | I      | 1100111| 000   |         |
| sb          | S      | 0100011| 000   |         |
| sw          | S      | 0100011| 010   |         |
| sd          | S      | 0100011|       |         |
| sh          | S      | 0100011| 001   |         |
| beq         | SB     | 1100011| 000   |         |
| bne         | SB     | 1100011| 001   |         |
| bge         | SB     | 1100011| 101   |         |
| blt         | SB     | 1100011| 100   |         |
| auipc       | U      | 0010111|       |         |
| lui         | U      | 0110111|       |         |
| jal         | UJ     | 1101111|       |         |


### Supported Instructions and Formats

1. **R Format**
   - **add rd, rs1, rs2**: Adds the values in registers rs1 and rs2 and stores the result in register rd.
   - **and rd, rs1, rs2**: Performs a bitwise AND operation between the values in registers rs1 and rs2 and stores the result in register rd.
   - **or rd, rs1, rs2**: Performs a bitwise OR operation between the values in registers rs1 and rs2 and stores the result in register rd.
   - **sll rd, rs1, rs2**: Performs a logical left shift of the value in register rs1 by the number of bits specified in register rs2 and stores the result in register rd.
   - **slt rd, rs1, rs2**: Sets rd to 1 if rs1 is less than rs2, otherwise sets rd to 0.
   - **sra rd, rs1, rs2**: Performs an arithmetic right shift of the value in register rs1 by the number of bits specified in register rs2 and stores the result in register rd.
   - **srl rd, rs1, rs2**: Performs a logical right shift of the value in register rs1 by the number of bits specified in register rs2 and stores the result in register rd.
   - **sub rd, rs1, rs2**: Subtracts the value in register rs2 from the value in register rs1 and stores the result in register rd.
   - **xor rd, rs1, rs2**: Performs a bitwise XOR operation between the values in registers rs1 and rs2 and stores the result in register rd.
   - **mul rd, rs1, rs2**: Multiplies the values in registers rs1 and rs2 and stores the lower 32 bits of the result in register rd.
   - **div rd, rs1, rs2**: Divides the value in register rs1 by the value in register rs2 and stores the quotient in register rd.
   - **rem rd, rs1, rs2**: Divides the value in register rs1 by the value in register rs2 and stores the remainder in register rd.

2. **I Format**
   - **addi rd, rs1, imm**: Adds the immediate value imm to the value in register rs1 and stores the result in register rd.
   - **andi rd, rs1, imm**: Performs a bitwise AND operation between the value in register rs1 and the immediate value imm and stores the result in register rd.
   - **ori rd, rs1, imm**: Performs a bitwise OR operation between the value in register rs1 and the immediate value imm and stores the result in register rd.
   - **lb rd, rs1, imm**: Loads a byte from the memory address calculated by adding the immediate value imm to the value in register rs1 and sign-extends it to 32 bits before storing it in register rd.
   - **ld rd, rs1, imm**: Loads a double word (64 bits) from the memory address calculated by adding the immediate value imm to the value in register rs1 and stores it in register rd.
   - **lh rd, rs1, imm**: Loads a half word (16 bits) from the memory address calculated by adding the immediate value imm to the value in register rs1 and sign-extends it to 32 bits before storing it in register rd.
   - **lw rd, rs1, imm**: Loads a word (32 bits) from the memory address calculated by adding the immediate value imm to the value in register rs1 and stores it in register rd.
   - **jalr rd, rs1, imm**: Sets rd to the address of the instruction following the jalr instruction, then jumps to the address calculated by adding the immediate value imm to the value in register rs1.

3. **S Format**
   - **sb rs2, imm (rs1)**: Stores the lowest byte of the value in register rs2 to the memory address calculated by adding the immediate value imm to the value in register rs1.

   
    **Note**: Ensure there is a space between imm and (rs1).

   - **sw rs2, imm (rs1)**: Stores the entire 32-bit value in register rs2 to the memory address calculated by adding the immediate value imm to the value in register rs1.
   - **sd rs2, imm (rs1)**: Stores the entire 64-bit value in register rs2 to the memory address calculated by adding the immediate value imm to the value in register rs1.
   - **sh rs2, imm (rs1)**: Stores the lowest half word (16 bits) of the value in register rs2 to the memory address calculated by adding the immediate value imm to the value in register rs1.
 

5. **SB Format**
   - **beq rs1, rs2, label**: Branches to the instruction at the specified label if the values in registers rs1 and rs2 are equal.
   - **bne rs1, rs2, label**: Branches to the instruction at the specified label if the values in registers rs1 and rs2 are not equal.
   - **bge rs1, rs2, label**: Branches to the instruction at the specified label if the value in register rs1 is greater than or equal to the value in register rs2.
   - **blt rs1, rs2, label**: Branches to the instruction at the specified label if the value in register rs1 is less than the value in register rs2.

6. **U Format**
   - **auipc rd, imm**: Adds the immediate value imm to the address of the current instruction (PC), sign-extends the result to 64 bits, and stores it in register rd.
   - **lui rd, imm**: Loads the immediate value imm into the upper 20 bits of register rd and zeroes out the lower 12 bits.

7. **UJ Format**
   - **jal rd, label**: Jumps to the instruction at the specified label and stores the address of the instruction following the jal instruction in register rd.

### Assembler Directives

In addition to instructions, the assembler supports the following directives:

- **.text**: Indicates the start of the text segment where instructions are located.
- **.data**: Indicates the start of the data segment where initialized data is located.
- **.byte**: Reserves space for one byte of data.
- **.half**: Reserves space for two bytes of data.
- **.word**: Reserves space for four bytes of data.
- **.dword**: Reserves space for eight bytes of data.
- **.asciiz**: Defines a null-terminated ASCII string.

Ensure each assembly directive is written on a separate line and followed by a space.

### Data Segment and Program Counter Information:

- **Data Segment Start Address**: 0x10000000
- **Program Counter (PC) Start Address**: 0x00000000
