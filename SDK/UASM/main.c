#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define INSTRUCTION_LENGTH 3
#define MAX_NUM_LENGTH 10  // Assume maximum length of a number in string form

void write_to_file(FILE *file, const char *code) {
    fwrite(code, sizeof(char), strlen(code), file);
}

void convert_number_to_binary(int number, char *binary_str) {
    // Converts an integer to a 4-bit binary string (change as needed)
    for (int i = 0; i < 4; i++) {
        binary_str[3 - i] = (number & (1 << i)) ? '1' : '0';
    }
    binary_str[4] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char *input_file_name = argv[1];
    const char *output_file_name = argv[2];

    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output_file = fopen(output_file_name, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), input_file)) {
        // Trim trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strncmp(buffer, "//", 2) == 0) {
            // Ignore comments
            continue;
        }

        char instruction[INSTRUCTION_LENGTH + 1] = {0};
        char num1_str[MAX_NUM_LENGTH] = {0};
        char num2_str[MAX_NUM_LENGTH] = {0};

        // Extract instruction
        strncpy(instruction, buffer, INSTRUCTION_LENGTH);
        instruction[INSTRUCTION_LENGTH] = '\0';

        // Extract numbers
        int num1, num2;
        if (sscanf(buffer + INSTRUCTION_LENGTH, "%d %d", &num1, &num2) == 2) {
            char num1_bin[5], num2_bin[5];
            convert_number_to_binary(num1, num1_bin);
            convert_number_to_binary(num2, num2_bin);

            if (strncmp(instruction, "ADD", INSTRUCTION_LENGTH) == 0) {
                write_to_file(output_file, "0001 ");
            } else if (strncmp(instruction, "SUB", INSTRUCTION_LENGTH) == 0) {
                write_to_file(output_file, "0010 ");
            } else {
                fprintf(stderr, "Unknown instruction: %s\n", instruction);
                continue;
            }

            // Write binary representations of the numbers
            write_to_file(output_file, num1_bin);
            write_to_file(output_file, " ");
            write_to_file(output_file, num2_bin);
            write_to_file(output_file, "\n");

        } else {
            fprintf(stderr, "Invalid format or missing numbers: %s\n", buffer);
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("Processing complete. Output written to %s\n", output_file_name);
    return 0;
}
