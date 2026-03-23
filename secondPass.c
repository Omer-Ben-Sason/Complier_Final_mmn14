#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */
#include "secondPass.h"

int foundErrorSecondPass = 0; /* global error flag for second pass */

/*
 * the func: replaceSymbolWithAddr
 * input: pointers to IC list, DC list, extern list, and entry list
 * output: memory struct with updated IC and DC lists
 */
void replaceSymbolWithAddr(symbolNode** headIC, symbolNode** headDC,
                            symbolNode** externs, symbolNode** entries, memory* mem)
{
    symbolNode* curr = *headIC;           /* current node in IC list */
    symbolNode* paramNode = NULL;         /* found label in symbol table */
    char* currData = NULL;                /* symbol data (label name) */
    char* currBianry = NULL;               /* binary string to store final value */
    int paramAddr = 0;                     /* address of referenced label */
    int lineNum = 0;                       /* line number counter */
    char binary[EVLEVEN_BIT] = {0};
    char* paramNodeName = NULL;

    while (curr) /* iterate through IC list */
    {
        lineNum++; /* increase line count */ 

        /* Allocate fresh binary template */
        currBianry = _strdup(CLEAR_MEM);
        if (!currBianry)
        {
            printf("Memory allocation failed in replaceSymbolWithAddr\n");
            foundErrorSecondPass = 1;
            return;
        }

        currData = curr->symbol->data; /* get data */

        /* if symbol data starts with a letter (label reference) */
        if (currData &&
            ((currData[0] >= BIG_A_ASCII && currData[0] <= BIG_Z_ASCII) ||
             (currData[0] >= SMALL_A_ASCII && currData[0] <= SMALL_Z_ASCII)))
        {
            /* symbol found and not an .entry */
            if ((paramNode = searchSymbolTable(currData, *headDC, *headIC, 1)) &&strcmp(curr->symbol->type, SYMBOL_ENT) != 0)
            {
                paramAddr = paramNode->symbol->addr << 2; /* calculate real address */

                if (strcmp(paramNode->symbol->type, SYMBOL_DATA) == 0 ||
                    strcmp(paramNode->symbol->type, SYMBOL_CODE) == 0)
                {
                    intToBinary(paramAddr, binary);
                    strcpy(currBianry, binary); /* convert to binary */
                    currBianry[8] = '1'; /* A = 1 */
                    currBianry[9] = '0'; /* R = 0, E = 0 */

                    /* Free old data if allocated */
                    if (curr->symbol->data)  
                    {
                        free(curr->symbol->data);
                    }
                    curr->symbol->data = currBianry; /* store result */
                }
                else if (strcmp(paramNode->symbol->type, SYMBOL_EXT) == 0)
                {
                    paramNodeName = paramNode->symbol->name;
                    if (!paramNodeName)
                    {
                        printf("Memory allocation failed in replaceSymbolWithAddr\n");
                        foundErrorSecondPass = 1;
                        free(currBianry);
                        return;
                    }

                    addSymbol(externs, paramNodeName, curr->symbol->addr, NULL, NULL); /* track extern */

                    /* Free old data if allocated */
                    if (curr->symbol->data)
                    {
                        free(curr->symbol->data);
                    }
                    curr->symbol->data = _strdup(CLEAR_MEM);
                    if (!curr->symbol->data)
                    {
                        printf("Memory allocation failed in replaceSymbolWithAddr\n");
                        foundErrorSecondPass = 1;
                        free(currBianry);
                        return;
                    }

                    currBianry[8] = '0'; /* A = 0 */
                    currBianry[9] = '1'; /* E = 1 */
                    free(curr->symbol->data); /* replace with final */
                    curr->symbol->data = currBianry;
                }
                else
                {
                    /* Not DATA or EXT — free unused binary */
                    free(currBianry);
                }
            } 
            else
            {
                if (strcmp(curr->symbol->type, SYMBOL_ENT) != 0)
                {
                    printf("param %s wasn't defined, define the label first!\n", currData);
                    foundErrorSecondPass = 1;
                }
                free(currBianry); /* not used */
            }
        }
        else
        {
            /* Not a label — free unused binary */
            free(currBianry);
        }

        curr = curr->next; /* go to next IC */
    }

    mem->headDC = *headDC; /* assign data */
    mem->headIC = *headIC; /* assign code */
}


/*
 * the func: secondPass
 * input: pointers to IC, DC, externs, entries
 * output: memory struct after second pass or cleared memory if error found
 */
void secondPass(symbolNode** headIC, symbolNode** headDC, symbolNode** externs, symbolNode** entries,memory* mem)
{
    replaceSymbolWithAddr(headIC, headDC, externs, entries,mem); /* resolve symbols */

    if (foundErrorSecondPass)
    {
        printf("Errors found in second pass, aborting.\n"); /* error msg */
        mem->headDC = NULL; /* clear data section */
        mem->headIC = NULL; /* clear code section */
        return ; /* return empty memory struct */
    }
    else
    {
        return ; /* return final result */
    }
}
/*
 * Function: getErrorPreassmbler
 * -----------------
 * returns stauts of flag
 *
 */
int getErrorSecondPass()
{
    return foundErrorSecondPass;
}