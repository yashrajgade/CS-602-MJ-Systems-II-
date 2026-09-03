# CS-602-MJ-Systems-II-
# Opcode Checker and Assembly Instruction Parser

This is a C++ program made for checking assembly instructions using an opcode table.

## What This Program Does

- Reads the opcode details from `instructions.txt`
- Reads the assembly program from `demo.asm`
- Checks if the mnemonic is present in the opcode table
- Shows whether the mnemonic is Found or Not Found
- Identifies the operands used in the instruction
- Identifies the type of operand

The operand types checked are:

- Register
- Constant
- Memory
- Symbol

The program also ignores:

- `global`
- `section`
- Labels
- Data directives
- Comments

## Problems Faced and Solutions

- **Reading opcode data:** Used a class and vector to store the opcode details.
- **Assembly directives and labels:** Ignored `global`, `section`, labels, and data directives.
- **Comments:** Removed comments starting with `;` before reading the instruction.
- **Operand types:** Checked whether an operand is a register, constant, memory, or symbol.
- **Invalid mnemonics:** Compared the mnemonic with the opcode table and showed **Found** or **Not Found**.


## Project Files

```text
Assignment_opcode_check/
├── Version1_1.cpp
├── demo.asm
└── instructions.txt



## Problems Faced and Solutions

- **Reading opcode data:** Used a class and vector to store the opcode details.
- **Assembly directives and labels:** Ignored `global`, `section`, labels, and data directives.
- **Comments:** Removed comments starting with `;` before reading the instruction.
- **Operand types:** Checked whether an operand is a register, constant, memory, or symbol.
- **Invalid mnemonics:** Compared the mnemonic with the opcode table and showed **Found** or **Not Found**.
