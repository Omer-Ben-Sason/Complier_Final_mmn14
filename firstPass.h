#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "preassembler.h"    /* for reservedNode tree */
#include "linkedList.h"      /* for symbolNode */
#include "utils.h"           /* common utilities */
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */

/* ===== CONSTANTS ===== */
#define DC_START 0                     /* data counter start */
#define IC_START 100                   /* instruction counter start */
#define DOT '.'                        /* dot character */
#define FOUR_BITS 4                    /* 4 bits constant */
#define SYMBOL_DATA ".data"           /* .data directive */
#define SYMBOL_MAT ".mat"             /* .mat directive */
#define SYMBOL_STRING ".string"       /* .string directive */
#define SYMBOL_EXT ".extern"          /* .extern directive */
#define SYMBOL_ENT ".entry"           /* .entry directive */
#define SYMBOL_CODE "code"            /* code type label */
#define REGISTER_SYMBOL "register"    /* register label */
#define LABAL_LEN 31                  /* max label length */
#define COLOM ':'                     /* colon character */
#define BUFF_SIZE 81                  /* buffer size for strings */
#define ZERO_ASCII '0'                /* ASCII for '0' */
#define NINE_ASCII '9'                /* ASCII for '9' */
#define LEFT_BRACKET '['              /* [ */
#define RIGHT_BRACKET ']'             /* ] */
#define MINUS_ASCII '-'               /* minus sign */
#define PLUS_ASCII '+'                /* plus sign */
#define CLEAR_MEM "0000000000"        /* 10-bit cleared memory */
#define TEN_BITS 10                   /* 10 bits */
#define SIX_BITS 6                    /* 6 bits */
#define EIGHT_BITS 8                  /* 8 bits */
#define COMMA_ASCII ','               /* comma character */
#define ASCII_BUF_SIZE 12             /* ASCII string buffer size */
#define MAX_PARAMS 10                 /* max parameters per instruction */
#define ONE_ASCII '1'                 /* ASCII for '1' */
#define TWO_ASCII '2'                 /* ASCII for '2' */
#define THREE_ASCII '3'               /* ASCII for '3' */
#define BIG_A_ASCII 'A'               /* ASCII for 'A' */
#define BIG_Z_ASCII 'Z'               /* ASCII for 'Z' */
#define SMALL_A_ASCII 'a'             /* ASCII for 'a' */
#define SMALL_Z_ASCII 'z'             /* ASCII for 'z' */

/* ===== STRUCTS ===== */
/*
 * Struct: memory
 * --------------
 * Holds the heads of the DC (data) and IC (code) symbol tables.
 */
typedef struct memory {
    symbolNode* headDC; /* head of data section */
    symbolNode* headIC; /* head of instruction/code section */
} memory;

/* ===== FUNCTION DECLARATIONS ===== */

/*
 * Function: checkIfValidMatParam
 * ------------------------------
 * Checks if a parameter string has the correct [x][y] matrix format.
 *
 * params: string to check
 * 
 * returns: 1 if valid matrix, 0 if malformed, -1 if no brackets
 */
int checkIfValidMatParam(char* params);

/*
 * Function: firstPass
 * -------------------
 * Performs the first pass of the assembler.
 *
 * root: reserved word tree
 * file: pointer to source file
 * entHead: pointer to entry list head
 *
 * returns: memory struct with headDC and headIC
 */
void firstPass(reservedNode* root, FILE* file, symbolNode** entHead,memory*);

/*
 * Function: isNumeric
 * -------------------
 * Checks if the given string is a valid integer.
 *
 * str: input string
 *
 * returns: 1 if numeric, 0 otherwise
 */
int isNumeric(char* str);

/*
 * Function: putInDC
 * -----------------
 * Parses and encodes .data, .string, or .mat content into the DC list.
 *
 * type: directive type (.data/.string/.mat)
 * restOfLine: content of the directive
 * lineNum: line number in file
 * head: pointer to head of DC list
 * name: label name
 * DC: pointer to DC counter
 *
 * returns: number of symbols added
 */
int putInDC(char* type, char* restOfLine, int lineNum, symbolNode** head, char* name, int* DC);

/*
 * Function: checkIfLabal
 * ----------------------
 * Validates if a string is a proper label and not a reserved word.
 *
 * labal: candidate label string
 * root: reserved word tree
 * lineNum: current line number
 * DC, IC: pointers to current symbol lists
 *
 * returns: label name if valid, NULL otherwise
 */
char* checkIfLabal(char* labal, reservedNode* root, int lineNum, symbolNode* DC, symbolNode* IC);

/*
 * Function: buildSymbols
 * ----------------------
 * Parses all lines and builds the symbol tables (first pass logic).
 *
 * root: reserved word tree
 * file: source file pointer
 * entHead: pointer to entry symbol list
 *
 * returns: memory struct
 */
void buildSymbols(reservedNode* root, FILE* file, symbolNode** entHead,memory*);

/*
 * Function: getErrorFirstPass
 * -----------------
 * returns stauts of flag
 *
 */
int getErrorFirstPass();

/*
 * Function: getMemoryCount
 * -----------------
 * returns ocunt of memory
 *
 */
int getMemoryCount();
/*
 * Function: putInIC
 * -----------------
 * Encodes and stores instructions and operands into the IC list.
 *
 * IC: pointer to instruction counter
 * restOfLine: line containing instruction operands
 * lineNum: line number
 * head: pointer to head of IC list
 * name: label name
 * root: reserved word tree
 * lastReg: pointer to last register binary string
 * inst: instruction name
 */
void putInIC(int* IC, char* restOfLine, int lineNum, symbolNode** head, char* name, reservedNode* root, char* inst);

/*
 * Function: countRestOfLine
 * -------------------------
 * Skips the opcode/label and returns a pointer to the rest of the line.
 *
 * line: full line from source file
 * isLabal: 1 if line starts with label, 0 otherwise
 *
 * returns: pointer to the remaining part of the line
 */
char* countRestOfLine(char* line, int isLabal);

/*
 * Function: handleData
 * --------------------
 * Handles the .data directive and adds numbers to DC list.
 *
 * curr: line after .data
 * lineNum: current line number
 * head: pointer to DC list
 * name: label name
 * DC: pointer to data counter
 * type: data type
 *
 * returns: number of symbols added
 */
int handleData(char* curr, int lineNum, symbolNode** head, char* name, int* DC, char* type);

/*
 * Function: handleString
 * ----------------------
 * Handles the .string directive and adds characters to DC list.
 *
 * curr: line after .string
 * lineNum: current line number
 * head: pointer to DC list
 * name: label name
 * DC: pointer to data counter
 *
 * returns: number of symbols added
 */
int handleString(char* curr, int lineNum, symbolNode** head, char* name, int* DC);

/*
 * Function: handleMat
 * -------------------
 * Handles the .mat directive and adds matrix values to DC list.
 *
 * curr: line after .mat
 * lineNum: current line number
 * head: pointer to DC list
 * name: label name
 * DC: pointer to data counter
 *
 * returns: number of symbols added
 */
int handleMat(char* curr, int lineNum, symbolNode** head, char* name, int* DC);

#endif
