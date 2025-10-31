 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTR_SIZE 3
#define OPCODE_SIZE 8

int main() {
    int locctr, start, length;
    FILE *fp_in, *fp_out, *fp_mneumonic;
    char label[10], opcode[10], operand[10];
    char mneumonic[][10] = {"LDA", "STA", "START", "END", "LDX", "STX", "LDCH", "STCH"};

    fp_in = fopen("INPUT.DAT", "r");
    fp_out = fopen("OUTPUT.DAT", "w");
    fp_mneumonic = fopen("SYMTAB.DAT", "w");

    // Check if files opened successfully
    // Note: Using || (logical OR) is generally safer than | (bitwise OR) for file checks.
    if (fp_in == 0 || fp_out == 0 || fp_mneumonic == 0) {
        printf("File Error\n");
        return 0;
    }

    fscanf(fp_in, "%s%s%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = strtol(operand, NULL, 16);
        locctr = start;
        fprintf(fp_out, "%4s\t%4s\t%04X\n", label, opcode, start);
        fscanf(fp_in, "%s%s%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp_out, "%04X\t", locctr);

        if (strcmp(label, "**") != 0) {
            fprintf(fp_mneumonic, "%s\t%04X\n", label, locctr);
        }

        int found = 0;
        for (int i = 0; i < OPCODE_SIZE; i++) {
            if (strcmp(opcode, mneumonic[i]) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * atoi(operand));
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                locctr += (strlen(operand) - 3);
            } else {
                printf("WARNING:UNKNOWN OPCODE %s\n", operand);
            }
        }

        fprintf(fp_out, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp_in, "%s%s%s", label, opcode, operand);
    }

    fprintf(fp_out, "%s\t%s\n", label, opcode);
    length = locctr - start;
    printf("LENGTH=%Xbytes\n", length);

    fclose(fp_in);
    fclose(fp_out);
    fclose(fp_mneumonic);
}
