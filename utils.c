#include "shell.h"

char **split_string(char *string, char *delimiter)
{
	char **words = malloc(sizeof(char *) * MAX_WORDS);
	char *token;
	int num_words = 0;

	token = strtok(string, delimiter);
	while (token != NULL)
	{
		words[num_words++] = token;
		token = strtok(NULL, delimiter);
	}

	words[num_words] = NULL;

	return (words);
}
