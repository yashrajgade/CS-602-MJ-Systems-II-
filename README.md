# CS-602-MJ-Systems-II

# One-Pass IA-32 Assembler

**A C++-based assembler prototype for instruction analysis, data representation, symbol management, and machine-code generation.**

## Overview

The **One-Pass IA-32 Assembler** is a C++ project developed as part of the CS-602 MJ Systems-II course. It explores the fundamental concepts of assembler design, focusing on opcode-table processing, data-directive conversion, memory-offset calculation, symbol-table construction, and initial instruction encoding.

The project demonstrates how assembly-language source files can be processed and how data can be represented in hexadecimal form according to IA-32 conventions.

## Features

- Reads opcode definitions from `instructions.txt`.
- Reads assembly-language source code from `demo.asm`.
- Processes `DB` and `DD` data directives.
- Converts characters and strings into hexadecimal ASCII representations.
- Converts 32-bit integer values into hexadecimal format.
- Represents multi-byte integers in Little-Endian format.
- Calculates data offsets according to declaration sizes.
- Maintains a basic symbol table.
- Checks instruction mnemonics against the opcode table.
- Supports initial instruction analysis and selected machine-code encoding.
- Provides a foundation for generating structured assembly listings.

## Data Directive Processing

### 1. DB (Define Byte)

The `DB` directive is used to declare byte-sized data, including characters, strings, and numeric values.

**Example:**

```asm
name db "yash",10,0
grade db 'A'
```

Implemented functionality:

- Converts characters into hexadecimal ASCII values.
- Processes string declarations.
- Handles multiple values separated by commas.
- Calculates the number of bytes occupied by each declaration.
- Updates data offsets accordingly.

### 2. DD (Define Doubleword)

The `DD` directive is used to declare 32-bit integer values.

**Example:**

```asm
Arr dd 60,11,56
num dd 10
```

Implemented functionality:

- Converts decimal integers into hexadecimal representation.
- Represents each integer using four bytes.
- Stores multi-byte values in Little-Endian order.
- Processes multiple integer values in one declaration.
- Calculates offsets based on the declared data size.

## Little-Endian Representation

IA-32 uses Little-Endian byte ordering, meaning the least significant byte is stored first.

For example, the decimal value `60` has the following 32-bit hexadecimal representation:

```text
0000003C
```

Its Little-Endian representation is:

```text
3C 00 00 00
```

The program applies this byte ordering when processing integer values declared using `DD`.

## Data Offset Calculation

The program calculates memory offsets according to the number of bytes occupied by each declaration.

**Example:**

```asm
section .data
    Arr     dd 60,11,56
    a       dd 20,28,55
    num     dd 10
    name    db "yash",10,0
    message db "hello",10,0
    grade   db 'A'
```

### Calculated Data Layout

| Symbol | Directive | Offset | Size |
|---|---|---|---|
| Arr | DD | `0x00` | 12 bytes |
| a | DD | `0x0C` | 12 bytes |
| num | DD | `0x18` | 4 bytes |
| name | DB | `0x1C` | 6 bytes |
| message | DB | `0x22` | 7 bytes |
| grade | DB | `0x29` | 1 byte |

This demonstrates how the size of each declaration determines the starting offset of the next symbol.

## Symbol Table

The project maintains a basic symbol table to organize information about declared symbols.

The symbol table includes:

- Symbol name
- Memory offset
- Declared size
- Symbol type

This provides a foundation for understanding how assemblers associate symbolic identifiers with memory locations.

## Instruction Processing

The program reads instruction definitions from `instructions.txt` and uses the opcode table during instruction analysis.

The current implementation supports initial stages of instruction processing, including:

- Mnemonic lookup.
- Operand-type identification.
- Opcode-table matching.
- Selected instruction-encoding operations.
- Hexadecimal representation of supported instruction bytes.

Instruction encoding is currently limited to selected instruction forms and does not cover the complete IA-32 instruction set.

## Project Structure

```text
CS-602-MJ-Systems-II/
├── main.cpp
├── instructions.txt
├── demo.asm
└── README.md
```

| File | Description |
|---|---|
| `main.cpp` | Contains the C++ implementation. |
| `instructions.txt` | Stores opcode and instruction-format information. |
| `demo.asm` | Contains assembly-language input for testing. |
| `README.md` | Documents the project and its functionality. |

*Note: Update the source filename in this structure if your actual C++ file uses a different name.*

## Technologies Used

- **Language:** C++
- **Target Architecture:** IA-32 (32-bit x86)
- **Operating System:** Linux
- **Compiler:** GCC
- **Input:** Assembly source file and opcode-definition file

### Concepts Covered

- Assembler Design
- Opcode Tables
- Assembly-Language Processing
- Data Directives
- Hexadecimal Conversion
- Little-Endian Representation
- Memory Offset Calculation
- Symbol Tables
- Instruction Encoding

## Compilation and Execution

### Step 1: Compile the Program

```bash
g++ main.cpp -o assembler
```

If your source file has a different name, replace `main.cpp` with the correct filename.

### Step 2: Run the Program

```bash
./assembler
```

Ensure that `instructions.txt` and `demo.asm` are available at the file locations expected by the program.

## Current Limitations

The current implementation is an educational assembler prototype, with functionality developed incrementally.

The following features are not yet fully implemented:

- Complete IA-32 instruction-set support.
- Full ModR/M and SIB encoding for all addressing modes.
- Comprehensive displacement and immediate-value handling.
- Complete label resolution and forward-reference processing.
- A fully implemented two-pass assembly process.
- Machine-code generation for arbitrary assembly programs.
- Complete syntax and operand validation.

These limitations define the current development scope and provide opportunities for future enhancement.

## Future Enhancements

- Expand support for IA-32 instruction formats.
- Improve operand validation and instruction selection.
- Implement additional ModR/M and SIB addressing modes.
- Add displacement and immediate-value encoding.
- Improve symbol resolution and label handling.
- Extend assembly listing generation.
- Develop a structured two-pass assembly workflow.
- Test the implementation using additional assembly programs.

## Conclusion

The **One-Pass IA-32 Assembler** provides a practical foundation for understanding assembler construction through C++ and systems programming.

By combining opcode-table processing, data-directive conversion, Little-Endian representation, memory-offset calculation, symbol-table management, and initial instruction encoding, the project connects theoretical concepts from computer architecture and system software with practical implementation.

The current implementation establishes a foundation for progressively developing a more complete IA-32 assembler.

---

**Course:** CS-602 MJ Systems-II  
**Project:** One-Pass IA-32 Assembler  
**Language:** C++  
**Architecture:** IA-32 (32-bit x86)
