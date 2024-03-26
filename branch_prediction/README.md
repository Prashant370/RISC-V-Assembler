# Branch Prediction

## Overview

The Branch Prediction module contains implementations of various branch prediction algorithms in C++. These algorithms include one-bit and two-bit predictors, as well as always taken and always not taken predictors. Both static and dynamic predictors are covered.

## Contents

- `Advanced_Test`: Folder containing advanced test cases for the Branch Prediction module.
- `Basic_Test/`: Folder containing basic test cases for the Branch Prediction module.
- `main2.cpp`: Main file containing the code for the Branch Prediction algorithms.

## Usage

To run the Branch Prediction module:

1. Prepare the input trace file in the following format:
    - Each line should represent a branch instruction.
    - Format: `core <core_number>: PC (<Machine Code>) branch_instruction rs1, rs2, offset_value (pc + [0-9]+)`
    - Example: `core 0: 0x80000288 (0x00629063) bne t0, t1, pc + 0`
    - Save the input trace file as `input.txt`.

2. Run the compiled executable:
    ```
    ./branch_prediction
    ```

3. Ensure that the output files are generated:
    - `BTB.txt`: Branch Target Buffer details.
    - `BHT_NT.txt`: Branch History Table details for the Always Not Taken predictor.
    - `BHT_T.txt`: Branch History Table details for the Always Taken predictor.
    - `BHT_oneBit.txt`: Branch History Table details for the One-Bit predictor.
    - `BHT_twoBit.txt`: Branch History Table details for the Two-Bit predictor.

## Note

- Only conditional branches are considered for prediction as non-conditional branches are always taken.
- The accuracy of each predictor is provided in the output files.

## Additional Information

For more detailed instructions and examples, refer to the specific README files in each module directory.
