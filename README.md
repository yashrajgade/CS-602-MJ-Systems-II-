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

The program reads instruction definitions from `instructions.txt` and uses the
