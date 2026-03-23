#include "linkedList.h"

/*
 * the func: addSymbol
 * input: head of list, symbol name, address, type, and data
 * output: none (adds symbol at end of list)
 */
void addSymbol(symbolNode** head, char* name, int address, char* type, char* data)
{
    symbolNode* node = malloc(sizeof(*node));  
    if (!node) 
    {
        printf("Memory allocation failed for symbol node\n");
        return;
    }

    node->symbol = malloc(sizeof(*node->symbol));  
    if (!node->symbol)
     {
        printf("Memory allocation failed for symbol\n");
        free(node);  
        return;
    }

    node->symbol->name = name ? _strdup(name) : NULL;  
    if (name && !node->symbol->name) 
    {
        printf("Memory allocation failed for name\n");
        free(node->symbol);
        free(node);
        return;
    }

    node->symbol->addr = address;  
    node->symbol->type = type ? _strdup(type) : NULL;  
    if (type && !node->symbol->type)
     {
        printf("Memory allocation failed for type\n");
        free(node->symbol->name);
        free(node->symbol);
        free(node);
        return;
    }

    node->symbol->data = data ? _strdup(data) : NULL;  
    if (data && !node->symbol->data) 
    {
        printf("Memory allocation failed for data\n");
        free(node->symbol->type);
        free(node->symbol->name);
        free(node->symbol);
        free(node);
        return;
    }

    node->next = NULL;  

    if (*head == NULL) 
    {  
        *head = node;
    } 
    else 
    {  
        symbolNode* temp = *head;
        while (temp->next) 
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

/*
 * the func: deleteNode
 * input: head of list, pointer to node to delete
 * output: none (removes node and shifts addresses)
 */
void deleteNode(symbolNode** head, symbolNode* nodeToDelete)
{
    symbolNode* curr = *head; /* current node */
    symbolNode* prev = NULL; /* previous node */
    symbolNode* update = NULL; /* for updating addresses */

    if (!head || !*head || !nodeToDelete) return; /* invalid input */

    if (curr == nodeToDelete) /* node is head */
    {
        *head = curr->next;
        update = *head;
    }
    else
    {
        while (curr && curr != nodeToDelete)
        {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return; /* not found */

        prev->next = curr->next; /* remove node */
        update = curr->next;
    }

    while (update) /* shift addresses */
    {
        update->symbol->addr--;
        update = update->next;
    }

    if (nodeToDelete&&nodeToDelete->symbol)
    {
        free(nodeToDelete->symbol->name); /* free name */
        free(nodeToDelete->symbol->type); /* free type */
        free(nodeToDelete->symbol->data); /* free data */
        free(nodeToDelete->symbol); /* free struct */
    }
    free(nodeToDelete); /* free node */
}

/*
 * the func: insertSymbolSortedByAddr
 * input: head of list, symbol name, address, type, and data
 * output: none (inserts in address-sorted order)
 */
void insertSymbolSortedByAddr(symbolNode** head, char* name, int address, char* type, char* data)
{
    symbolNode* node = malloc(sizeof(*node));  
    if (!node) {
        printf("Memory allocation failed for symbol node\n");
        return;
    }

    node->symbol = malloc(sizeof(*node->symbol));  
    if (!node->symbol) {
        printf("Memory allocation failed for symbol\n");
        free(node);  
        return;
    }

    node->symbol->name = name ? _strdup(name) : NULL;  
    if (name && !node->symbol->name) {
        printf("Memory allocation failed for name\n");
        free(node->symbol);
        free(node);
        return;
    }

    node->symbol->addr = address;  
    node->symbol->type = type ? _strdup(type) : NULL;  
    if (type && !node->symbol->type) {
        printf("Memory allocation failed for type\n");
        free(node->symbol->name);
        free(node->symbol);
        free(node);
        return;
    }

    node->symbol->data = data ? _strdup(data) : NULL;  
    if (data && !node->symbol->data) {
        printf("Memory allocation failed for data\n");
        free(node->symbol->type);
        free(node->symbol->name);
        free(node->symbol);
        free(node);
        return;
    }

    node->next = NULL;  

    if (*head == NULL || (*head)->symbol->addr > address) 
    {  
        node->next = *head;
        *head = node;
    } 
    else
    {
        symbolNode* curr = *head;
        while (curr->next && curr->next->symbol->addr < address) {  
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;  
    }
}

/*
 * the func: printSymbols
 * input: head of list
 * output: none (prints all symbols)
 */
void printSymbols(symbolNode* head)
{
    if (!head) return;

    printf("addr: %d\tname: %s\tdata: %s\ttype: %s\n",
           head->symbol->addr,
           (head->symbol->name) ? head->symbol->name : "\0",
           (head->symbol->data) ? head->symbol->data : "0",
           (head->symbol->type) ? head->symbol->type : "\0");

    printSymbols(head->next); /* recurse */
}

/*
 * the func: findSymbol
 * input: head of list, target name
 * output: pointer to symbol if found, NULL otherwise
 */
symbol* findSymbol(symbolNode* head, char* name)
{
    while (head) 
    {
        if (strcmp(head->symbol->name, name) == 0) return head->symbol;
        head = head->next;
    }
    return 0;
}

/*
 * the func: findSymbolNode
 * input: head of list, target name
 * output: pointer to node if found, NULL otherwise
 */
symbolNode* findSymbolNode(symbolNode* head, char* name)
{
    while (head)
    {
        if (head->symbol && strcmp(head->symbol->name, name) == 0)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

/*
 * the func: freeSymbolTable
 * input: head of list
 * output: none (frees entire symbol list)
 */
void freeSymbol(symbol* sym) 
{
    if (sym) 
    {
        if (sym->name) 
        {
            free(sym->name);  
        }
        if (sym->type) 
        {
            free(sym->type);  
        }
        if (sym->data) 
        {
            free(sym->data); 
        }
        if (sym) free(sym);  
    }
}
/*
 * the func: freeSymbolTable
 * input: head of list
 * output: none (frees entire symbol list)
 */
void freeSymbolTable(symbolNode* head)
{
    symbolNode* next = NULL;
    while (head) 
    {
        next = head->next; 
        if (head->symbol)  
        {
            freeSymbol(head->symbol); 
        }
        if (head) free(head); 
        head = next;
    }

}