# CS-602-MJ-Systems-II

# One-Pass IA-32 Assembler

This is a C++ project developed as part of the CS-602 MJ Systems-II course. The project focuses on reading assembly program files, processing data directives, and converting data into hexadecimal representation according to IA-32 conventions.

## What This Program Does

- Reads opcode details from `instructions.txt`.
- Reads the assembly program from `demo.asm`.
- Reads and processes `DB` and `DD` data directives.
- Converts character and string data into hexadecimal values.
- Converts integer values declared using `DD` into 32-bit hexadecimal representation.
- Stores `DD` values in Little-Endian format.
- Calculates data offsets according to the number of bytes occupied by each declaration.
- Displays the hexadecimal representation along with the corresponding offsets.
- Supports the initial stages of assembly instruction processing using an opcode table.

## Data Directives

### DB (Define Byte)

- Stores character, string, and byte-sized numeric data.
- Converts characters into their hexadecimal ASCII values.
- Processes multiple values separated by commas.
- Increases the data offset according to the number of bytes stored.

### DD (Define Doubleword)

- Stores 32-bit integer values.
- Converts integer values into hexadecimal representation.
- Stores each value in Little-Endian format.
- Processes multiple values separated by commas.
- Increases the data offset by four bytes for each value.

## Little-Endian Format

In IA-32, multi-byte values are stored with the least significant byte first.

For example:

Decimal value:
```text
60
