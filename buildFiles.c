#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */
#include "buildFiles.h"

/*
 * the func: buildEntryFile
 * input: fileName, IC head, DC head, entry symbols list
 * output: content for .ent file (dynamically allocated)
 */
char* buildEntryFile(char* fileName, symbolNode* headIC, symbolNode* headDC, symbolNode* entries)
{
    symbolNode* curr = entries; /* current entry node */
    char* fileText = (char*)malloc(LEN); /* allocate memory for file content */
    char line[LEN] = {0}; /* line buffer */
    int lineCount = 1; /* line count for realloc */
    char base4[20] = {0}; /* enough for big numbers */
    char* addrStr =NULL;
    fileText[0] = '\0'; /* initialize file text */

    while (curr) /* loop through entries */
    {
        symbolNode* target = searchSymbolTable(curr->symbol->name, headDC, headIC, 1); /* find actual symbol */

        if (target) /* if found */
        {
            
            intToBinary(target->symbol->addr, base4);
            addrStr = base4;
            
            sprintf(line, "%s %s\n", curr->symbol->name, addrStr); /* format line */
            fileText = realloc(fileText, LEN * (++lineCount)); /* reallocate for new line */
            strcat(fileText, line); /* append line */
        }
        curr = curr->next; /* move to next entry */
    }

    return fileText; /* return file content */
}

/*
 * the func: buildExternFile
 * input: fileName, list of extern symbols
 * output: content for .ext file
 */
char* buildExternFile(char* fileName, symbolNode* externs)
{
    symbolNode* curr = externs; /* current node */
    int lineCount = 0; /* line counter */
    char* fileText = (char*)malloc(LEN); /* allocate file buffer */
    char line[LEN] = {0}; /* line buffer */
    char base4[20] = {0}; /* enough for big numbers */
    fileText[0] = '\0'; /* init file text */

    while (curr) /* iterate externs */
    {
        intToBinary(curr->symbol->addr, base4);
        sprintf(line, "%s %s\n", curr->symbol->name, base4); /* build line */
        lineCount++; /* count lines */
        fileText = realloc(fileText, LEN * lineCount); /* grow buffer */
        if (!fileText)
        {
            printf("Memory reallocation failed\n");
            return NULL;
        }
        strcat(fileText, line); /* append line */
        curr = curr->next; /* move to next */
    }
    return fileText; /* return final text */
}

/*
 * the func: buildObjectFile
 * input: fileName, IC and DC lists
 * output: .ob file contents
 */
char* buildObjectFile(char* fileName, symbolNode* headIC, symbolNode* headDC)
{
    char* fileText = (char*)malloc(LEN); /* buffer for file text */
    symbolNode* curr = headIC; /* current node */
    int lineCount = 1; /* line counter */
    char line[LEN] = {0}; /* line buffer */
    int IC_len = 0; /* length of IC */
    int DC_len = 0; /* length of DC */
    char base4[20] = {0}; /* enough for big numbers */
    char IC_bin[20] = { 0 };
    char DC_bin[20] = { 0 };
    fileText[0] = '\0'; /* empty string */

    /* count IC lines */
    curr = headIC;
    while (curr != headDC)
    {
        if (!(strcmp(curr->symbol->type, SYMBOL_ENT) == 0 || strcmp(curr->symbol->type, SYMBOL_EXT) == 0))
        {
            IC_len++;
        }
        curr = curr->next;
    }

    /* count DC lines */
    curr = headDC;
    while (curr)
    {
        if (!(strcmp(curr->symbol->type, SYMBOL_ENT) == 0 || strcmp(curr->symbol->type, SYMBOL_EXT) == 0))
        {
            DC_len++;
        }
        curr = curr->next;
    }

    fileText = realloc(fileText, LEN); /* make sure it's at least one line */


    intToBinary(IC_len, IC_bin);
    intToBinary(DC_len, DC_bin);

    sprintf(fileText, "\t%s %s\n", IC_bin, DC_bin);

    curr = headIC;
    while (curr)
    {
        char* result = NULL;

        if (!(strcmp(curr->symbol->type, SYMBOL_ENT) == 0 || strcmp(curr->symbol->type, SYMBOL_EXT) == 0))
        {
            lineCount++;
            fileText = realloc(fileText, LEN * lineCount);
            if (!fileText)
            {
                printf("Memory reallocation failed\n");
                return NULL;
            }
            intToBinary(curr->symbol->addr, base4);
            result = _strdup(curr->symbol->data);
            sprintf(line, "%s %s\n",base4, result);
            free (result);
            strcat(fileText, line);
        }
        curr = curr->next;
    }
    return fileText;
}

/*
 * the func: buildFiles
 * input: fileName, DC list, IC list, extern and entry symbols
 * output: writes .ent, .ext, and .ob files to disk
 */
void buildFiles(char* fileName, symbolNode* headDC, symbolNode* headIC, symbolNode* externs, symbolNode* entries)
{
    char* entContent = NULL; /* entry file content */
    char* extContent = NULL; /* extern file content */
    char* objectContent = NULL; /* object file content */

    char* entFileName = NULL; /* .ent file name */
    char* extFileName = NULL; /* .ext file name */
    char* objFileName = NULL; /* .ob file name */

    if (entries) /* only if entries exist */
    {
        entContent = buildEntryFile(fileName, headIC, headDC, entries);
    }

    if (externs) /* only if externs exist */
    {
        extContent = buildExternFile(fileName, externs);
    }

    objectContent = buildObjectFile(fileName, headIC, headDC); /* always build object */

    entFileName = malloc(strlen(fileName) + FIVE_CHARS); /* ".ent" + '\0' */
    extFileName = malloc(strlen(fileName) + FIVE_CHARS); /* ".ext" + '\0' */
    objFileName = malloc(strlen(fileName) + FIVE_CHARS); /* ".ob"  + '\0' */

    if (!entFileName || !extFileName || !objFileName) /* check allocations */
    {
        printf("Memory allocation failed for entFileName or extFileName or objFileName\n");
        return;
    }

    sprintf(entFileName, "%s.ent", fileName); /* create full file name */
    sprintf(extFileName, "%s.ext", fileName);
    sprintf(objFileName, "%s.ob", fileName);

    /* write .ent file */
    if (entContent && *entContent)
    {
        FILE* entFile = fopen(entFileName, WRITE_MODE); /* open file */
        if (entFile)
        {
            fprintf(entFile, "%s", entContent); /* write content */
            fclose(entFile); /* close file */
        }
        free(entContent); /* free buffer */
    }

    /* write .ext file */
    if (extContent && *extContent)
    {
        FILE* extFile = fopen(extFileName, WRITE_MODE);
        if (extFile)
        {
            fprintf(extFile, "%s", extContent);
            fclose(extFile);
        }
        free(extContent);
    }

    /* write .ob file */
    if (objectContent)
    {
        FILE* objectFile = fopen(objFileName, WRITE_MODE);
        if (objectFile)
        {
            fprintf(objectFile, "%s", objectContent);
            fclose(objectFile);
        }
        free(objectContent);
    }

    /* free file name buffers */
    if (entFileName) free(entFileName);
    if (extFileName) free(extFileName);
    if (objFileName) free(objFileName);
}
