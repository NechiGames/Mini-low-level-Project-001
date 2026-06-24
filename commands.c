#include "commands.h"
#include <stdlib.h>
#include <string.h>

void handle_comment(const char *arg, FILE *boot)
{
    fprintf(boot, "; %s\n", arg);
}

void handle_cli(const char *arg, FILE *boot)
{
    fprintf(boot, "cli\n");
}

void handle_hlt(const char *arg, FILE *boot)
{
    fprintf(boot, "hlt\n");
}

void handle_jmp(const char *arg, FILE *boot)
{
    fprintf(boot, "jmp %s\n", arg);
}

void handle_multiboot(const char *arg, FILE *boot)
{
    fprintf(boot, "section .multiboot\n");
}

void handle_stext(const char *arg, FILE *boot)
{
    fprintf(boot, "section .text\n");
}

void handle_global_st(const char *arg, FILE *boot)
{
    fprintf(boot, "global _start\n");
}

void handle_extern(const char *arg, FILE *boot)
{
    fprintf(boot, "extern %s\n", arg);
}

void handle_call(const char *arg, FILE *boot)
{
    fprintf(boot, "call %s\n", arg);
}

void handle_st(const char *arg, FILE *boot)
{
    fprintf(boot, "_start:\n");
}

void handle_align(const char *arg, FILE *boot)
{
    int value = atoi(arg);
    fprintf(boot, "align %d\n", value);
}

void handle_dd(const char *arg, FILE *boot)
{
    if (strcmp(arg, "MAGIC") == 0)
    {
        fprintf(boot, "dd 0x1BADB002\n");
    }
    else if (strcmp(arg, "FLAG") == 0)
    {
        fprintf(boot, "dd 0\n");
    }
    else if (strcmp(arg, "CHECKSUM") == 0)
    {
        fprintf(boot, "dd -(0x1BADB002)\n");
    }
    else
    {
        int value = atoi(arg);
        fprintf(boot, "dd %d\n", value);
    }
}
