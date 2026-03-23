#include "binaryTree.h"

/*
the func: height
input: reservedNode* node - pointer to a node in the tree
output: int - height of the node (0 if null)
*/
int height(reservedNode* node)
{
    return node ? node->height : 0; /* return node height or 0 if null */
}


/*
the func: getBalance
input: reservedNode* node - pointer to a node
output: int - balance factor (left height - right height)
*/
int getBalance(reservedNode* node)
{
    return node ? height(node->left) - height(node->right) : 0; /* return balance or 0 if null */
}

/*
the func: rotateRight
input: reservedNode* y - root of unbalanced subtree
output: reservedNode* - new root after right rotation
*/
reservedNode* rotateRight(reservedNode* y)
{
    reservedNode* x = y->left;       /* left child */
    reservedNode* T2 = x->right;     /* subtree */

    x->right = y;    /* perform rotation */
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1; /* update height */
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; /* return new root */
}

/*
the func: rotateLeft
input: reservedNode* x - root of unbalanced subtree
output: reservedNode* - new root after left rotation
*/
reservedNode* rotateLeft(reservedNode* x)
{
    reservedNode* y = x->right;      /* right child */
    reservedNode* T2 = y->left;      /* subtree */

    y->left = x;     /* perform rotation */
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1; /* update height */
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; /* return new root */
}

/*
the func: createNode
input: char* name, char* pData, char* type, char* opDst, char* opSrc, char* binary
output: reservedNode* - pointer to newly created node
*/
reservedNode* createNode(char* name, char* pData, char* type, char* opDst, char* opSrc, char* binary)
{
    reservedNode* node = (reservedNode*)malloc(sizeof(reservedNode)); /* allocate node */
    node->reserved = (reserved*)malloc(sizeof(reserved)); /* allocate inner struct */

    node->reserved->name = _strdup(name); /* duplicate and assign name */ 
    node->reserved->pData = pData ? _strdup(pData) : 0; /* duplicate or NULL */
    node->reserved->type = type ? _strdup(type) : 0;
    node->reserved->opDst = opDst ? _strdup(opDst) : 0;
    node->reserved->opSrc = opSrc ? _strdup(opSrc) : 0;
    node->reserved->binary = binary ? _strdup(binary) : 0;

    node->left = 0;   /* init left child */
    node->right = 0;  /* init right child */
    node->height = 1; /* new node height is 1 */

    return node; /* return pointer to node */
}

/*
the func: insertNode
input: reservedNode* node, char* name, pData, type, opDst, opSrc, binary
output: reservedNode* - new root of subtree after insert and balancing
*/
reservedNode* insertNode(reservedNode* node, char* name, char* pData, char* type, char* opDst, char* opSrc, char* binary)
{
    int cmp = 0;       /* comparison result */
    int balance = 0;   /* balance factor */

    if (!node) /* base case - create new node */
    {
        return createNode(name, pData, type, opDst, opSrc, binary);
    }

    cmp = strcmp(name, node->reserved->name); /* compare names */

    if (cmp < 0) /* go left */
    {
        node->left = insertNode(node->left, name, pData, type, opDst, opSrc, binary);
    }
    else if (cmp > 0) /* go right */
    {
        node->right = insertNode(node->right, name, pData, type, opDst, opSrc, binary);
    }
    else /* duplicate key - do nothing */
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right)); /* update height */
    balance = getBalance(node); /* calculate balance */

    /* Left Left */
    if (balance > 1 && strcmp(name, node->left->reserved->name) < 0)
        return rotateRight(node);

    /* Right Right */
    if (balance < -1 && strcmp(name, node->right->reserved->name) > 0)
        return rotateLeft(node);

    /* Left Right */
    if (balance > 1 && strcmp(name, node->left->reserved->name) > 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    /* Right Left */
    if (balance < -1 && strcmp(name, node->right->reserved->name) < 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; /* return unchanged node */
}

/*
the func: findNode
input: reservedNode* root, char* name - root of tree and target name
output: reservedNode* - pointer to node with matching name or NULL
*/
reservedNode* findNode(reservedNode* root, char* name)
{
    int cmp = 0; /* comparison result */
    if (!root) return 0; /* base case: not found */

    cmp = strcmp(name, root->reserved->name); /* compare names */

    if (cmp == 0) /* found */
    {
        return root;
    }
    else if (cmp < 0) /* go left */
    {
        return findNode(root->left, name);
    }
    else /* go right */
    {
        return findNode(root->right, name);
    }
}

/*
the func: printInOrder
input: reservedNode* root - root of tree
output: none (prints to stdout)
*/
void printInOrder(reservedNode* root)
{
    if (!root) return; /* base case */

    printInOrder(root->left); /* left */

    printf("%s %s %s\n", 
           root->reserved->name, /* print name */
           root->reserved->type ? root->reserved->type : "NULL", /* type or NULL */
           root->reserved->binary ? root->reserved->binary : "NULL"); /* binary or NULL */

    printInOrder(root->right); /* right */
}

/*
the func: freeTree
input: reservedNode* root - root of tree
output: none (frees memory)
*/
void freeTree(reservedNode* root)
{
    if (!root) return; /* base case */

    freeTree(root->left);  /* free left subtree */
    freeTree(root->right); /* free right subtree */
    free(root->reserved->name);   /* free name */
    free(root->reserved->pData);  /* free pData */
    free(root->reserved->type);   /* free type */
    free(root->reserved->opDst);  /* free opDst */
    free(root->reserved->opSrc);  /* free opSrc */
    free(root->reserved->binary);/* free binary */
    free(root->reserved);        /* free reserved struct */
    free(root);                  /* free node */
}
