#ifndef _SIMPLE_SHELL_
#define _SIMPLE_SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_WORDS 100

extern char **environ;
char **split_string_to_words(char *string, char *separator);
int exit_code(char **words, char *argv[]);
void free_words(char **words);

#endif
