#if !defined(VALIANT__STRING_H)
#define VALIANT__STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct valiant_SplitString
{
    int count;
    const char** items;
} valiant_SplitString;

/// <summary>
/// Concatenate two strings together.
/// </summary>
char* valiant_String_Concat(const char *s1, const char *s2);

/// <summary>
/// Split a string by a delimiter.
/// </summary>
valiant_SplitString* valiant_String_Split(const char* input, const char* delimiter);

/// <summary>
/// Unload the result of `valiant_String_Split`.
/// </summary>
void valiant_String_Split_Unload(valiant_SplitString* splitString);

#endif // VALIANT__STRING_H
