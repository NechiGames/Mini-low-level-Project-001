#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>

typedef void (*CommandHandler)(const char *arg, FILE *boot);

typedef struct
{
    const char *name;
    CommandHandler handler;
} Command;

void generate_asm(const char *input, const char *output_asm);

void handle_comment(const char *arg, FILE *boot);
void handle_cli(const char *arg, FILE *boot);
void handle_hlt(const char *arg, FILE *boot);
void handle_jmp(const char *arg, FILE *boot);
void handle_multiboot(const char *arg, FILE *boot);
void handle_stext(const char *arg, FILE *boot);
void handle_global_st(const char *arg, FILE *boot);
void handle_extern(const char *arg, FILE *boot);
void handle_call(const char *arg, FILE *boot);
void handle_st(const char *arg, FILE *boot);
void handle_align(const char *arg, FILE *boot);
void handle_dd(const char *arg, FILE *boot);

#endif
