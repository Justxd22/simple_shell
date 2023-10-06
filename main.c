#include "shell.h"


/**
 * handle_shell_cmds - takes cmds and execute them
 * @words: commands + their args to execute
 * No Return
 */
void handle_shell_cmds(char **words)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("ERROR FORK\n");
		exit(100);
	}
	else if (pid == 0)
	{
		if (execvp(words[0], words) == -1)
		{
			printf("Not a COmmand?? %s\n", words[0]);
			//exit(99);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			printf("Error Child\n");
			exit(101);
		}
	}
}

/**
 * main - main func for the simple shell
 * Return: 0
 */
int main(void)
{
	size_t input_size = 0, read_bytes;
	char *separator = " ", *input = NULL, **words;
	int x = 0;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		read_bytes = getline(&input, &input_size, stdin);

		if (read_bytes == -1)
		{
			printf("\n");
			break;
		}

		input[read_bytes - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("\n");
			break;
		}

		words = split_string(input, separator);

		handle_shell_cmds(words);

		for (x = 0; words[x] != NULL; x++)
			printf("x%d : %s\n", x, words[x]);

		input = NULL;
		free_words(words);
	}

	free(words);
	return (0);
}
