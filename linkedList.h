#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */

/* 
 * Struct: symbol
 * --------------
 * Represents a symbol with its name, address, type, and binary data.
 */
typedef struct symbol {
    char* name;     /* symbol name (label) */
    int addr;       /* symbol address (IC/DC) */
    char* type;     /* type: code, data, extern, entry */
    char* data;     /* binary or string data */
} symbol;

/* 
 * Struct: symbolNode
 * ------------------
 * Linked list node containing a symbol.
 */
typedef struct symbolNode {
    symbol* symbol;             /* pointer to the symbol */
    struct symbolNode* next;   /* pointer to next node */
} symbolNode;

#include "utils.h" /* includes utility macros and constants */

/*
 * Function: addSymbol
 * -------------------
 * Adds a new symbol to the end of the list.
 *
 * head: pointer to the head of the symbol list
 * name: symbol name
 * address: address to assign
 * type: type of symbol
 * data: associated binary or string data
 */
void addSymbol(symbolNode** head, char* name, int address, char* type, char* data);

/*
 * Function: findSymbol
 * --------------------
 * Searches for a symbol by name and returns the symbol struct.
 *
 * head: head of the symbol list
 * name: name to search for
 *
 * returns: pointer to the symbol if found, otherwise NULL
 */
symbol* findSymbol(symbolNode* head, char* name);

/*
 * Function: freeSymbolTable
 * -------------------------
 * Frees all memory in the symbol list.
 *
 * head: head of the list
 */
void freeSymbolTable(symbolNode* head);

/*
 * Function: printSymbols
 * ----------------------
 * Recursively prints all symbols in the list.
 *
 * head: head of the list
 */
void printSymbols(symbolNode* head);

/*
 * Function: insertSymbolSortedByAddr
 * ----------------------------------
 * Inserts a symbol into the list in ascending address order.
 *
 * head: pointer to the list head
 * name: symbol name
 * address: address to assign
 * type: type of symbol
 * data: binary data string
 */
void insertSymbolSortedByAddr(symbolNode** head, char* name, int address, char* type, char* data);

/*
 * Function: deleteNode
 * --------------------
 * Deletes a node from the list and updates following addresses.
 *
 * head: pointer to list head
 * nodeToDelete: pointer to the node to delete
 */
void deleteNode(symbolNode** head, symbolNode* nodeToDelete);

/*
 * Function: findSymbolNode
 * ------------------------
 * Finds and returns the symbolNode that matches the given name.
 *
 * head: head of the list
 * name: symbol name
 *
 * returns: pointer to the node, or NULL if not found
 */
symbolNode* findSymbolNode(symbolNode* head, char* name);

#endif
