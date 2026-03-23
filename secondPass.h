#ifndef SECONDPASS_H
#define SECONDPASS_H

#include "utils.h"        /* utility constants and helper functions */
#include "firstPass.h"    /* memory struct and symbolNode definitions */

/*
 * Function: replaceSymbolWithAddr
 * -------------------------------
 * Resolves label references in the IC list to actual memory addresses.
 * Replaces textual label names with binary-encoded addresses.
 * Also tracks .extern symbols used and updates externs list.
 *
 * headIC: pointer to head of instruction symbol list
 * headDC: pointer to head of data symbol list
 * externs: pointer to list of extern symbols used
 * entries: pointer to list of entry symbols
 *
 * returns: memory struct with updated IC and DC lists
 */
void replaceSymbolWithAddr(symbolNode** headIC, symbolNode** headDC, symbolNode** externs, symbolNode** entries,memory*);

/*
 * Function: secondPass
 * --------------------
 * Performs the second pass of the assembler.
 * Calls replaceSymbolWithAddr and handles error state.
 *
 * headIC: pointer to head of instruction symbol list
 * headDC: pointer to head of data symbol list
 * externs: pointer to extern list (will be updated)
 * entries: pointer to entry list (unchanged)
 *
 * returns: memory struct (IC and DC lists), or empty if errors occurred
 */
void secondPass(symbolNode** headIC, symbolNode** headDC, symbolNode** externs, symbolNode** entries,memory*);
/*
 * Function: getErrorPreassmbler
 * -----------------
 * returns stauts of flag
 *
 */
int getErrorSecondPass();

#endif
