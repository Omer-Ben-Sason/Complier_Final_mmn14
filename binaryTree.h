#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "utils.h"
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */

/* 
 * Struct: reserved
 * Represents a reserved word or macro
 */
typedef struct reserved {
    char* name;    /* name of the reserved word */
    char* pData;   /* additional data (if any) */
    char* type;    /* type: instruction, directive, etc. */
    char* opDst;   /* valid destination operand */
    char* opSrc;   /* valid source operand */
    char* binary;  /* binary representation */
} reserved;

/* 
 * Struct: reservedNode
 * AVL tree node to hold reserved data
 */
typedef struct reservedNode {
    reserved* reserved;           /* pointer to reserved data */
    struct reservedNode* left;   /* left child */
    struct reservedNode* right;  /* right child */
    int height;                  /* height of the node */
} reservedNode;

/* 
 * Function: height
 * input: reservedNode* node - pointer to tree node
 * output: int - height of the node (0 if null)
 */
int height(reservedNode* node);

/* 
 * Function: getBalance
 * input: reservedNode* node - pointer to tree node
 * output: int - balance factor (left height - right height)
 */
int getBalance(reservedNode* node);

/* 
 * Function: rotateRight
 * input: reservedNode* y - unbalanced node
 * output: reservedNode* - new root after right rotation
 */
reservedNode* rotateRight(reservedNode* y);

/* 
 * Function: rotateLeft
 * input: reservedNode* x - unbalanced node
 * output: reservedNode* - new root after left rotation
 */
reservedNode* rotateLeft(reservedNode* x);

/* 
 * Function: createNode
 * input: name, pData, type, opDst, opSrc, binary - fields to create a reserved
 * output: reservedNode* - pointer to a new AVL tree node
 */
reservedNode* createNode(char* name, char* pData, char* type, char* opDst, char* opSrc, char* binary);

/* 
 * Function: insertNode
 * input: node - current root, plus reserved fields to insert
 * output: reservedNode* - new root of balanced subtree
 */
reservedNode* insertNode(reservedNode* node, char* name, char* pData, char* type, char* opDst, char* opSrc, char* binary);

/* 
 * Function: findNode
 * input: root - tree root, name - target reserved word
 * output: reservedNode* - node containing name, or NULL
 */
reservedNode* findNode(reservedNode* root, char* name);

/* 
 * Function: printInOrder
 * input: root - tree root
 * output: none (prints in-order traversal to stdout)
 */
void printInOrder(reservedNode* root);

/* 
 * Function: freeTree
 * input: root - tree root
 * output: none (frees all memory in the tree)
 */
void freeTree(reservedNode* root);

#endif
