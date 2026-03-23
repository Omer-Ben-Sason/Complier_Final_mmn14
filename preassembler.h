#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include "binaryTree.h"   /* for reservedNode and AVL tree functions */
#include "utils.h"        /* for constants and utility functions */
#include <stdio.h>        /* for FILE operations */

/* ===== MACROS ===== */
#define LEN 81                     /* max line length */
#define EOL '\n'                  /* end-of-line character */
#define EVLEVEN_BIT 11            /* 11 bits (not used directly here) */
#define MCRO_START "mcro"         /* macro start keyword */
#define MCRO_END "mcroend"        /* macro end keyword */
#define FOUR_BYTES 4              /* used for extensions like ".am" */
#define ZERO_ASCII '0'            /* ASCII code for '0' */
#define SEVEN_ASCII '7'           /* ASCII code for '7' */

/* ===== FUNCTION DECLARATIONS ===== */

/*
 * Function: initReservedWords
 * ---------------------------
 * Initializes the reserved word tree with instructions, directives, and registers.
 *
 * root: pointer to the root of the reserved AVL tree
 */
void initReservedWords(reservedNode** root);
/*
 * Function: getErrorPreassmbler
 * -----------------
 * returns stauts of flag
 *
 */
int getErrorPreassmbler();

/*
 * Function: loadLine
 * ------------------
 * Reads one line from a file.
 *
 * file: pointer to opened file
 *
 * returns: dynamically allocated line (must be freed)
 */
char* loadLine(FILE* file);

/*
 * Function: freeWords
 * -------------------
 * Frees the array returned by breakLine.
 *
 * words: array of strings
 */
void freeWords(char** words);

/*
 * Function: findMcro
 * ------------------
 * Parses and stores macros from a file into a reservedNode tree.
 * Writes resulting expanded content to an output file if valid.
 *
 * file: input file pointer
 * root: pointer to reservedNode tree
 * outputFileName: base name for output file (.am)
 */
void findMcro(FILE* file, reservedNode* root, char* outputFileName);

/*
 * Function: preassmble
 * --------------------
 * Runs the full preassembler: macro parsing, validation, and output generation.
 *
 * inputFile: pointer to the original .as file
 * inputFileName: base name (without extension)
 * root: reservedNode tree to hold macros
 *
 * returns: pointer to opened .am file (output of macro expansion)
 */
FILE* preassmble(FILE* inputFile, char* inputFileName, reservedNode* root);

#endif
