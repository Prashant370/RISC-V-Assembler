# RISC-V Assembler and Branch Prediction

This repository contains implementations of a RISC-V Assembler and Branch Prediction algorithms, developed as part of a course project under the guidance of [Dr. T.V Kalyan](https://sites.google.com/view/kalyantv) and [Dr. Neeraj Goel](https://sites.google.com/view/neerajgoel).

## RISC-V Assembler

### Overview

The RISC-V Assembler module provides functionality to convert assembly code written in RISC-V syntax into machine code. It supports various RISC-V instructions and assembler directives.

### Contents

- `main1.cpp`: Main file containing the code for the RISC-V Assembler.
- `advanced_tests`: Folder containing advanced test cases for the RISC-V Assembler.
- `basic_tests/`: Folder containing basic test cases for the RISC-V Assembler.

### Usage

#### Windows

To use the RISC-V Assembler on Windows:

1. Open Command Prompt.
2. Navigate to the directory containing `main1.cpp`.
3. Compile the code using the following command:
    ```
    g++ main1.cpp -o riscv_assembler.exe
    ```
4. Prepare the RISC-V assembly code file.
5. Run the compiled executable, providing the RISC-V assembly code file as input:
    ```
    riscv_assembler.exe <input_file>
    ```

#### Linux and macOS

To use the RISC-V Assembler on Linux and macOS:

1. Open Terminal.
2. Navigate to the directory containing `main1.cpp`.
3. Compile the code using the following command:
    ```
    g++ main1.cpp -o riscv_assembler
    ```
4. Prepare the RISC-V assembly code file.
5. Run the compiled executable, providing the RISC-V assembly code file as input:
    ```
    ./riscv_assembler <input_file>
    ```

## Branch Prediction

### Overview

The Branch Prediction module consists of implementations for various branch prediction algorithms, including one-bit and two-bit predictors, as well as always taken and always not taken predictors. Both static and dynamic predictors are covered.

### Contents

- `Advanced_Test`: Folder containing advanced test cases for the Branch Prediction module.
- `Basic_Test/`: Folder containing basic test cases for the Branch Prediction module.
- `main2.cpp`: Main file containing the code for the Branch Prediction algorithms.

### Usage

#### Windows

To run the Branch Prediction module on Windows:

1. Open Command Prompt.
2. Navigate to the directory containing `main2.cpp`.
3. Compile the code using the following command:
    ```
    g++ main2.cpp -o branch_prediction.exe
    ```
4. Run the compiled executable:
    ```
    branch_prediction.exe
    ```

#### Linux and macOS

To run the Branch Prediction module on Linux and macOS:

1. Open Terminal.
2. Navigate to the directory containing `main2.cpp`.
3. Compile the code using the following command:
    ```
    g++ main2.cpp -o branch_prediction
    ```
4. Run the compiled executable:
    ```
    ./branch_prediction
    ```

## Team Members

| Name                     | Entry Number |
|--------------------------| -------------|
| [Pranav Dipesh Bhole](https://github.com/pranavbhole123) | 2022CSB1103  |
| [Prashant Kumar](https://github.com/Prashant370)            | 2022CSB1202  |
| [Kartikey Sahu](https://github.com/kartikeysahu987)          | 2022CSB1087  |

## Technology Stack

1. C++
2. Assembly Language (RISC-V ISA)

## Additional Information

For more detailed instructions and examples, refer to the specific README files in each module directory.

