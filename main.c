#include "main.h"
/*
 * Omer Ben Sason
 * 332873454
 */
int countMemory = 0;
/*
 * the func: main
 * input: argc (number of args), argv (array of args)
 * output: int (0 on success, 1 on failure)
 */
int main(int argc, char** argv)
{
    int i = 0; /* index for files */

    if (argc < 2) /* no input files given */
    {
        printf("format: <file1> <file2> ...\n"); /* print usage */
        return 1; /* exit with error */
    }

    for (i = 1; i < argc; i++) /* iterate over all input files */
    {
        runAssembler(argv[i]); /* process each file */
        if (countMemory>255)
        {
            printf("the max memory is 256 and yourse is %d\n",countMemory);
            break;
        }

    }

 /* Free all allocated memory at the end */
    return 0; /* success */
}

/*
 * the func: runAssembler
 * input: inputFileName (file name without extension)
 * output: none (runs the full assembler pipeline)
 */
void runAssembler(char* inputFileName)
{
    reservedNode* root = NULL;            /* root of reserved words tree */
    FILE* outputFileAm = NULL;            /* pointer to .am file */
    symbolNode* externs = NULL;           /* list of .extern labels */
    symbolNode* entries = NULL;           /* list of .entry labels */
    memory mem = {0};                     /* memory struct holding symbol tables */
    FILE* inputFile = NULL;               /* pointer to original .as file */
    char* sourceFile = NULL;              /* buffer for file name */

    initReservedWords(&root);             /* load all reserved words into tree */

    sourceFile = malloc(sizeof(char) * (strlen(inputFileName) + FOUR_BYTES)); /* allocate space for "file.as" */
    sprintf(sourceFile, "%s.as", inputFileName);    /* format full file name */

    inputFile = fopen(sourceFile, "r");   /* open source file */

    if (!inputFile) /* check if open failed */
    {
        printf("Failed to open %s\n", sourceFile); /* error msg */
        freeTree(root);             /* free reserved word tree */
        if (sourceFile) free (sourceFile) ;
        if (outputFileAm) fclose(outputFileAm); 
        return; /* stop */
    }
    if (countMemory>255)
    {
        printf("the max memory is 256 and yourse is %d\n",countMemory);
    }
    outputFileAm = preassmble(inputFile, inputFileName, root); /* expand macros */
    if (!getErrorPreassmbler())
    {
        firstPass(root, outputFileAm, &entries,&mem);             /* perform first pass */
        countMemory += getMemoryCount();
        if (!getErrorFirstPass())
        {
            secondPass(&mem.headIC, &mem.headDC, &externs, &entries,&mem); /* perform second pass */
            if (!getErrorSecondPass())
            {
                buildFiles(inputFileName, mem.headDC, mem.headIC, externs, entries); /* generate .ob/.ent/.ext */
            }
        }
    }

    freeTree(root);             /* free reserved word tree */
    if (externs) freeSymbolTable(externs);    /* free externs table */
    externs = NULL;
    if (mem.headDC) freeSymbolTable(mem.headDC); /* free instruction table */ 
    mem.headDC = NULL;
    if (mem.headIC) freeSymbolTable(mem.headIC); /* free instruction table */ 
    mem.headIC = NULL;
    if (entries) freeSymbolTable(entries);       /* free entries table */ 
    if (sourceFile) free (sourceFile) ;
    if (outputFileAm) fclose(outputFileAm);   /* close .am file */ 
}