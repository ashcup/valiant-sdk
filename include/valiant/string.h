#if !defined(VALIANT__STRING_H)
#define VALIANT__STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Valiant_SplitString
{
    int count;
    const char** items;
} Valiant_SplitString;

/// <summary>
/// Concatenate two strings together.
/// </summary>
char* Valiant_String_Concat(const char *s1, const char *s2);

/// <summary>
/// Split a string by a delimiter.
/// </summary>
Valiant_SplitString* Valiant_String_Split(const char* input, const char* delimiter);

/// <summary>
/// Unload the result of `Valiant_String_Split`.
/// </summary>
void Valiant_String_Split_Unload(Valiant_SplitString* splitString);

#endif // VALIANT__STRING_H
