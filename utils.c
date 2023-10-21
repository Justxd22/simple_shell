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
		if (strchr(token, '#') != NULL)
		{
			if (token[0] == '#')
			{
				if (num_words == 0)
					words[num_words++] = "#";
				break;
			}
		}
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
	free(words);
}


/**
 * exit_code - figure out exit code
 * @words: contains words + exit
 * @argv: to get program name
 * Return: code 36/37/0/{custom}
 */
int exit_code(char **words, char *argv[])
{
	int code = atoi(words[1]);

	if (code <= 0)
	{
		fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", argv[0], words[1]);
		return (2);
	}
	else
		return (code);
}
