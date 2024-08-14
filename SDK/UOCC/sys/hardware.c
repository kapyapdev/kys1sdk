#include "hardware.h"

FILE *outputFile;

void init(FILE* f)
{
    outputFile = f;
}

int add(int a, int b)
{
    char aStr[50];
    char bStr[50];
    char result[150]; // Buffer to hold the final concatenated string

    // Convert integers to strings
    sprintf(aStr, "%d", a);
    sprintf(bStr, "%d", b);

    // Create the final string with concatenation
    strcpy(result, "ADD ");        // Start with "ADD "
    strcat(result, aStr);          // Append integer a as string
    strcat(result, " ");           // Add a space
    strcat(result, bStr);          // Append integer b as string
    strcat(result, "\n");          // Add a newline

    // Write the final string to the file
    fprintf(outputFile, "%s", result);

    int r = a+b;

    return r;
}

int sub(int a, int b)
{
    char aStr[50];
    char bStr[50];
    char result[150]; // Buffer to hold the final concatenated string

    // Convert integers to strings
    sprintf(aStr, "%d", a);
    sprintf(bStr, "%d", b);

    // Create the final string with concatenation
    strcpy(result, "SUB ");        // Start with "SUB "
    strcat(result, aStr);          // Append integer a as string
    strcat(result, " ");           // Add a space
    strcat(result, bStr);          // Append integer b as string
    strcat(result, "\n");          // Add a newline

    // Write the final string to the file
    fprintf(outputFile, "%s", result);

    int r = a-b;

    return r;
}
