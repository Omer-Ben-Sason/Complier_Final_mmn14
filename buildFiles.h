#ifndef BUILD_FILES
#define BUILD_FILES

#include "utils.h"         /* utility definitions and functions */
#include "firstPass.h"     /* definitions related to symbolNode */
#define _CRT_SECURE_NO_WARNINGS /* for Visual Studio to allow standard functions */

/*
 * Function: buildExternFile
 * -------------------------
 * Builds the content for the .ext file based on extern symbols.
 *
 * fileName: base name of the file (without extension)
 * externs: linked list of extern symbol nodes
 *
 * returns: dynamically allocated string containing the .ext file contents
 */
char* buildExternFile(char* fileName, symbolNode* externs);

/*
 * Function: buildEntryFile
 * ------------------------
 * Builds the content for the .ent file based on entry symbols.
 *
 * fileName: base name of the file (without extension)
 * headIC: head of the instruction list
 * headDC: head of the data list
 * entries: linked list of entry symbol nodes
 *
 * returns: dynamically allocated string containing the .ent file contents
 */
char* buildEntryFile(char* fileName, symbolNode* headIC, symbolNode* headDC, symbolNode* entries);

/*
 * Function: buildFiles
 * --------------------
 * Generates .ob, .ent, and .ext files if needed and writes them to disk.
 *
 * fileName: base name of the file (without extension)
 * headDC: head of the data symbol list
 * headIC: head of the instruction symbol list
 * externs: linked list of extern symbol nodes
 * entries: linked list of entry symbol nodes
 *
 * returns: void
 */
void buildFiles(char* fileName, symbolNode* headDC, symbolNode* headIC, symbolNode* externs, symbolNode* entries);

/*
 * Macro: WRITE_MODE
 * -----------------
 * File opening mode for writing (overwrite).
 */
#define WRITE_MODE "w"

/*
 * Macro: FIVE_CHARS
 * -----------------
 * Buffer size needed for file extensions like ".ent", ".ext", ".ob"
 */
#define FIVE_CHARS 5

#endif
