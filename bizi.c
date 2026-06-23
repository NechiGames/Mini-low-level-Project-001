#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"

void create_output_file(const char *input, const char *output)
{
    FILE *in = fopen(input, "r");
    if (!in)
    {
        printf("Error: Cannot open %s\n", input);
        return;
    }
    FILE *out = fopen(output, "w");
    if (!out)
    {
        printf("Error: Cannot create %s\n", output);
        fclose(in);
        return;
    }

    char ch;
    while ((ch = fgetc(in)) != EOF)
    {
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
    printf("Successfully generated intermediate file: %s\n", output);
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Usage:\n");
        printf("  Режим 1: bizi bizi/mboot.bizi -o out\n");
        printf("  Режим 2: bizi out -a multiboot/boot.asm\n");
        return 1;
    }

    char *input_file = argv[1];
    char *flag = argv[2];
    char *output_file = argv[3];

    if (strcmp(flag, "-o") == 0)
    {
        printf("Bizi Compiler [Mode: -o]\n");
        create_output_file(input_file, output_file);
    }
    else if (strcmp(flag, "-a") == 0)
    {
        printf("Bizi Compiler [Mode: -a]\n");
        generate_asm(input_file, output_file);
    }
    else
    {
        printf("Unknown flag: %s. Expected -o or -a\n", flag);
        return 1;
    }

    printf("Done.\n");
    return 0;
}
