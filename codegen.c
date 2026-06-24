#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "commands.h"

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#endif

static Command cmd_table[] = {
    {"; ", handle_comment},
    {"cli", handle_cli},
    {"hlt", handle_hlt},
    {"jmp ", handle_jmp},
    {"multiboot", handle_multiboot},
    {"stext", handle_stext},
    {"globalST", handle_global_st},
    {"extern ", handle_extern},
    {"call ", handle_call},
    {"ST: ", handle_st},
    {"align ", handle_align},
    {"dd ", handle_dd}};

#define CMD_COUNT (sizeof(cmd_table) / sizeof(Command))

static void ensure_directory(const char *path)
{
    char temp[256];
    snprintf(temp, sizeof(temp), "%s", path);
    char *p = strrchr(temp, '/');
    if (p)
    {
        *p = '\0';
        mkdir(temp, 0777);
    }
}

void generate_asm(const char *input, const char *output_asm)
{
    FILE *source = fopen(input, "r");
    if (!source)
    {
        printf("Error: Cannot open input file %s\n", input);
        return;
    }

    ensure_directory(output_asm);

    FILE *boot = fopen(output_asm, "w");
    if (!boot)
    {
        printf("Error: Cannot create/update %s\n", output_asm);
        fclose(source);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), source))
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }

        if (len > 1 && line[len - 1] == ':')
        {
            fprintf(boot, "%s\n", line);
            continue;
        }

        int matched = 0;
        for (size_t i = 0; i < CMD_COUNT; i++)
        {
            size_t name_len = strlen(cmd_table[i].name);
            if (strncmp(line, cmd_table[i].name, name_len) == 0)
            {
                cmd_table[i].handler(line + name_len, boot);
                matched = 1;
                break;
            }
        }
    }

    fclose(source);
    fclose(boot);
    printf("Successfully updated: %s\n", output_asm);
}
