#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */

/* Include the macro expansion phase (preassembler) */
#include "preassembler.h"    /* for preassmble function and reserved words tree */

/* Include the first pass processing */
#include "firstPass.h"       /* for firstPass and memory struct */

/* Include the second pass processing */
#include "secondPass.h"      /* for secondPass and symbol updates */

/* Include file generation utilities */
#include "buildFiles.h"      /* for buildFiles function */

/* Include common utility macros */
#include "utils.h"           /* for constants and utility functions */

/* Standard library for variable arguments (optional) */
/*
 * Function: runAssembler
 * ----------------------
 * Performs the full assembler process (preassembler, first pass, second pass, output generation)
 *
 * inputFileName: base name of the input file (no extension)
 *
 * returns: void
 */
void runAssembler(char* inputFileName);
/*
 * Function: freeAllAssemblerResources
 * -----------------------------------
 * Frees all allocated memory and closes any open files used in runAssembler.
 */
void freeAllAssemblerResources(reservedNode* root,symbolNode* externs,symbolNode* entries,memory* mem,char* sourceFile,FILE* outputFileAm);
/*
 * Function: main
 * --------------
 * Entry point of the assembler. Iterates over given file names and assembles each one.
 *
 * argc: argument count
 * argv: argument vector (file names)
 *
 * returns: 0 on success, 1 on failure
 */
int main(int argc, char** argv);

#endif
