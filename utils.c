#include "shell.h"

/**
 * split_string_to_words - string to words helper using strtok
 * @string: string to split
 * @separator: the separator char eg. ","
 * Return: words
 */
char **split_string_to_words(char *string, char *separator)
{
	char **words = malloc(sizeof(char *) * MAX_WORDS);
	char *token;
	int num_words = 0;

	token = strtok(string, separator);
	while (token != NULL)
	{
		words[num_words++] = token;
		token = strtok(NULL, separator);
	}

	words[num_words] = NULL;

	return (words);
}

/**
 * free_words - helper func to free a double pointer
 * @words: contains the malloc allocation to free
 * No Return
 */
void free_words(char **words)
{
	int x;

	for (x = 0; words[x] != NULL; x++)
	{
		free(words[x]);
	}
	free(words);
}
