# Assembler Project (mmn14)

## Overview

This project is a two-pass assembler written in C.
It processes assembly source files (`.as`) and generates output files:

* `.ob` – object file (binary)
* `.ent` – entry symbols
* `.ext` – external symbols

The assembler supports:

* Labels
* `.data`, `.string`, `.mat`
* `.entry`, `.extern`
* Instructions with multiple addressing modes
* Registers and immediate values

---

## How to Run

Build the project and run:

```
Complier_Final_mmn14.exe <file name>
```

Example:

```
Complier_Final_mmn14.exe file
```

---

## Example Files

There is an example input file located in:

```
x64/Release/
```

You can use it to test the assembler.

---

## Known Issues

* ⚠️ Macro (preassembler) functionality currently has a bug and does not work correctly.

---

## Notes

* Output files are created in the same directory as the input.
* The project was developed as part of an academic assignment.

---
