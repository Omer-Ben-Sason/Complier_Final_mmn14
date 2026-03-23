#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>     /* for FILE operations */
#include <stdlib.h>    /* for malloc, free, atoi */
#include <string.h>    /* for string functions */
#include "linkedList.h" /* for symbolNode definition */
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */
/* ===== MACROS ===== */
#define LEN 81              /* max line length including \0 */
#define EVLEVEN_BIT 11      /* number of bits in binary word + null terminator */
#define MAX_PARAMS 10       /* max parameters in a line or instruction */
#define NUMBER_FOUR 4
/* ===== FUNCTION DECLARATIONS ===== */
/*
 * Function: freeWords
 * -------------------
 * Frees an array of strings allocated by breakLine or breakToParams.
 *
 * words: NULL-terminated array of char* strings
 */
void freeWords(char** words);

/*
 * Function: breakLine
 * -------------------
 * Splits a line by whitespace and tabs.
 *
 * line: input line
 *
 * returns: array of tokens (strings), NULL-terminated
 */
void breakLine(char* line,char* commands[]);
char* strdup(char* src);
/*
 * Function: loadLine
 * ------------------
 * Reads a line from a file, dynamically allocating memory.
 *
 * file: pointer to the input file
 *
 * returns: pointer to a line string (must be freed)
 */
char* loadLine(FILE* file);

/*
 * Function: intToBinary
 * ---------------------
 * Converts an integer to a 10-bit binary string.
 *
 * num: number to convert
 *
 * returns: pointer to binary string (must be freed)
 */
void intToBinary(int num,char binary[EVLEVEN_BIT]);
/*
 * Function: searchSymbolTable
 * ---------------------------
 * Searches both DC and IC symbol tables for a symbol by name.
 *
 * name: label name to search
 * DC: data section symbol list
 * IC: instruction/code section symbol list
 * searchIC: if 1, also search IC list
 *
 * returns: pointer to found symbolNode, or NULL if not found
 */
symbolNode* searchSymbolTable(char* name, symbolNode* DC, symbolNode* IC, int searchIC);

/*
 * Function: breakToParams
 * -----------------------
 * Tokenizes a line into parameters, optionally splitting brackets as separate tokens.
 *
 * line: input line
 * breakBrackets: if 1, also split on '[' and ']'
 *
 * returns: NULL-terminated array of parameter strings
 */
char** breakToParams(char* line, int breakBrackets);

/*
 * Function: intToFourBase
 * -----------------------
 * Converts an integer to special base-4 representation (using characters).
 *
 * num: integer to convert
 *
 * returns: pointer to string in base-4 (must be freed)
 */
void intToFourBase(int num,char* base4);

/*
 * Function: isNumeric
 * -------------------
 * Checks if a string is a valid integer (with optional sign).
 *
 * str: string to check
 *
 * returns: 1 if valid integer, 0 otherwise
 */
int isNumeric(char* str);

/*
 * Function: binaryToFourBase
 * --------------------------
 * Converts a 10-bit binary string into base-4 format used by the assembler.
 *
 * binary: 10-char string containing binary digits
 *
 * returns: pointer to base-4 formatted string (must be freed)
 */
char* binaryToFourBase(char* binary);

#endif
