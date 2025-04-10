#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "valiant/string.h"

char* Valiant_String_Concat(const char *s1, const char *s2)
{
    // Add 1 to size to account for for the null-terminator character (`\0`).
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    // If we failed to allocate enough memory for the result, return `NULL`.
    if (result == NULL)
    {
        return NULL;
    }

    // Copy the first string into the result.
    strcpy(result, s1);

    // Append the second string onto the end of the result.
    strcat(result, s2);

    // Return the concatenated string.
    return result;
}

Valiant_SplitString* Valiant_String_Split(const char* input, const char* delimiter)
{
    // If the input is `NULL`, return `NULL`.
    if (!input) return NULL;

    // Make a copy of the input so strtok doesn't modify the original.
    char* buffer = strdup(input);
    if (!buffer) return NULL;

    // First, count how many items there are
    int count = 0;

    for (char* p = buffer; *p; p++)
    {
        if (*p == '\n') count++;
    }

    // One more line than number of newlines.
    count++;

    // Allocate space for line pointers.
    char** items = malloc(sizeof(char*) * count);

    // If `items` is `NULL`:
    if (!items)
    {
        // Free the buffer.
        free(buffer);

        // Return `NULL`.
        return NULL;
    }

    // Tokenize and fill the array
    int i = 0;
    char* token = strtok(buffer, delimiter);

    while (token)
    {
        // Copy each line.
        items[i++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    // Free the original copy (not the individual items).
    free(buffer);

    // Create the split string instance.
    Valiant_SplitString* splitString = malloc(sizeof(Valiant_SplitString));

    // Set the split string's fields.
    splitString->count = i;
    splitString->items = items;

    // Return the split string.
    return splitString;
}

void Valiant_String_Split_Unload(Valiant_SplitString* splitString)
{
    int count = splitString->count;
    char** items = splitString->items;

    for (int i = 0; i < count; i++)
    {
        free(items[i]);
    }

    free(items);
    free(splitString);
}
