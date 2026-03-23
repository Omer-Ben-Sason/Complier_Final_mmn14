#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

#define MAX_ALLOCATED_MEMORY 1000 /* Max number of memory allocations to track */

void* buffer[MAX_ALLOCATED_MEMORY]; /* Array to track allocated memory */
int bufferIndex = 0; /* Index to keep track of the next free position in the buffer */
void* buffer_free[MAX_ALLOCATED_MEMORY];
int bufferIndexFree = 0;
/* 
 * Frees dynamically allocated array of strings 
 * Input: array of strings
 * Output: none
 */
void freeWords(char** words) 
{
    int i = 0;
    if (words) 
    {
        for (i = 0; words[i] != NULL; i++) 
        {
            free(words[i]); /* free each word */
        }
    }
}
char* __strdup(char* src)
{
    char* copy=NULL;
    int len = 0;

    if (!src)
        return NULL;

    len = strlen(src);
    copy = (char*)malloc(len + 1); /* +1 for null terminator */

    if (!copy)
        return NULL;

    strcpy(copy, src);
    return copy;
}
/* 
 * Splits a line into tokens (words), returns a dynamically allocated array of words 
 * Input: string line
 * Output: dynamically allocated array of strings (tokens)
 */
void breakLine(char* line, char* commands[]) 
{
    int numWords = 0; /* number of words found */
    char* token = NULL;
    char tmp[LEN] = {0}; /* temporary line copy for tokenizing */

    memcpy(tmp,line,LEN);
    token = strtok(tmp, " \t\n"); /* first token */
    while (token != NULL) 
    {
        commands[numWords] = (char*)malloc(strlen(token) + 1); /* allocate memory for word */
        if (commands[numWords] == NULL) 
        {
            printf("Memory allocation failed for word\n");
            freeWords(commands); /* free the temporary string */
            return; /* return early on failure */
        }
        strcpy(commands[numWords], token); /* copy token */
        numWords++;

        token = strtok(NULL, " \t\n"); /* next token */
    }

    commands[numWords] = NULL; /* mark end of words */
}

/*
the func makes int to four base
input: int num
output: char* the string
*/
void intToFourBase(int num,char* base4) /* convert int to base-4 with a=b=0..3 */
{
    int i = 0;
    int j = 0;
    if (!base4)
    {
        printf("base4: NULL pointer\n");
        return;
    }

    if (num == 0)
    {
        base4[0] = 'a';
        base4[1] = '\0';
    }

    while (num > 0)
    {
        base4[i++] = 'a' + (num % NUMBER_FOUR); /* 0=a, 1=b, 2=c, 3=d */
        num /= 4;
    }

    base4[i] = '\0';

    /* reverse the string */
    for (j = 0; j < i / 2; j++)
    {
        char tmp = base4[j];
        base4[j] = base4[i - j - 1];
        base4[i - j - 1] = tmp;
    }
}
/* 
 * Reads a line from a file and returns a dynamically allocated string 
 * Input: pointer to input file
 * Output: dynamically allocated line string or NULL
 */
char* loadLine(FILE* file)
{
    char* line = (char*)malloc(LEN * sizeof(char)); /* buffer to hold the line */
    if (!line)
    {
        printf("Memory allocation failed for line\n");
        return 0;
    }

    if (fgets(line, LEN, file)) /* read line from file */
    {
        return line;
    }
    else
    {
        free(line);
    }
    return NULL;
}
/* 
 * turns an integer into its binary representation
 * Input: integer number
 *  * Output: integer representing the binary number
 */
void intToBinary(int num, char binary[EVLEVEN_BIT])
{
    int bits = EVLEVEN_BIT - 1;  
    unsigned int mask = (1 << bits) - 1; 
    int i = 0;

    num &= mask;  

    if (binary == NULL) {
        printf("Error: binary array is NULL!\n");
        return;
    }

    binary[bits] = '\0'; 

    for (i = bits - 1; i >= 0; i--)  
    {
        binary[i] = (num & 1) ? '1' : '0'; 
        num >>= 1;  
    }
}

/*
the func: breakToParams
input: a line of text, and a flag whether to break by brackets or not
output: an array of parameter strings (tokens), NULL-terminated
*/
char** breakToParams(char* line, int breakBrackets) /* main tokenizer */
{
    int paramCount = 0; /* number of tokens */
    char* token = NULL; /* current token */
    char* lineCopy = NULL; /* copy of the line */
    char** params = (char**)malloc(MAX_PARAMS * sizeof(char*)); /* array of tokens */

    if (!params) /* malloc check for params */
    {
        printf("Memory allocation failed for params\n"); /* error message */
        return NULL; /* return on fail */
    }

    lineCopy = _strdup(line); /* duplicate line */
    if (!lineCopy) /* malloc check for line copy */
    {
        printf("Memory allocation failed for line copy\n"); /* error message */
        if (params) free(params); /* free previously allocated params */
        return NULL; /* return on fail */
    }

    if (breakBrackets) /* decide delimiter set */
    {
        token = strtok(lineCopy, ",[] \t"); /* split with brackets */
    }
    else
    {
        token = strtok(lineCopy, ", \t"); /* split without brackets */
    }

    while (token != NULL && paramCount < MAX_PARAMS) /* loop tokens */
    {
        params[paramCount] = (char*)malloc(strlen(token) + 1); /* allocate for token */
        if (!params[paramCount]) /* malloc check */
        {
            printf("Memory allocation failed for param\n"); /* error message */
            break; /* exit loop */
        }

        strcpy(params[paramCount], token); /* copy token */
        paramCount++; /* next index */

        if (breakBrackets) /* next token with brackets */
        {
            token = strtok(NULL, ",[] \t"); /* continue split */
        }
        else
        {
            token = strtok(NULL, ", \t"); /* continue split */
        } 
    }

    params[paramCount] = NULL; /* null-terminate array */
    if (lineCopy) free(lineCopy); /* free duplicated line */
    return params; /* return array */
}
/*
the func: searchSymbolTable
input: label name, head of DC and IC symbol lists
output: pointer to symbol node if found, otherwise NULL
*/
symbolNode* searchSymbolTable(char* name, symbolNode* DC, symbolNode* IC,int searchIC) /* search for label in symbol tables */
{
    symbolNode* curr = DC; /* start with DC list */

    while (curr) /* iterate over DC */
    {
        if (curr->symbol->name && strcmp(curr->symbol->name, name) == 0) return curr; /* found match in DC */
        curr = curr->next; /* go to next */
    }
    if (searchIC)
    {
        curr = IC; /* switch to IC list */

        while (curr) /* iterate over IC */
        {
            if (curr->symbol->name && strcmp(curr->symbol->name, name) == 0) return curr; /* found match in IC */
            curr = curr->next; /* go to next */
        }
    }
    return NULL; /* not found */
}
/* 
the func: isNumeric
input: a string
output: 1 if numeric, else 0
*/
int isNumeric(char* str) /* checks if a string is a valid integer */
{
    if (*str == '+' || *str == '-') /* optional sign */
    {
        str++; /* skip sign */
    }

    if (*str == '\0') /* string was only '+' or '-' */
    {
        return 0; /* not numeric */
    }

    while (*str) /* loop through each character */
    {
        if (*str < '0' || *str > '9') /* not a digit */
        {
            return 0; /* invalid */
        }
        str++; /* next character */
    }

    return 1; /* valid number */
}
/*
the func: binaryToFourBase
input: binary string (10 bits)
output: base-4 string using a=0, b=1, c=2, d=3
*/
char* binaryToFourBase(char* binary)
{
    int i = 0, j = 0;
    int len = strlen(binary);
    int numGroups = len / 2;
    char* result = (char*)malloc(numGroups + 1); /* each 2 bits become one base-4 digit */
    if (!result)
    {
        printf("Memory allocation failed in binaryToFourBase\n");
        return NULL;
    }

    for (i = 0; i < len; i += 2)
    {
        int val = 0;
        if (binary[i] == '1') val += 2;
        if (binary[i + 1] == '1') val += 1;
        result[j++] = 'a' + val; /* a=0, b=1, c=2, d=3 */
    }

    result[j] = '\0';
    return result;
}

