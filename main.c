#include "shell.h"


/**
 * handle_shell_cmds - takes cmds and execute them
 * @words: commands + their args to execute
 * @argv: argv to get program name
 * No Return
 */
void handle_shell_cmds(char **words, char *argv[])
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
			printf("%s: No such file or directory\n", argv[0]);
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
 * @argc: args count
 * @argv: array of args
 * Return: 0
 */
int main(__attribute__((unused))int argc, char *argv[])
{
	size_t input_size = 0;
	ssize_t read_bytes;
	char *separator = " ", *input = NULL, **words = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");
		fflush(stdout);

		read_bytes = getline(&input, &input_size, stdin);

		if (read_bytes == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		input[read_bytes - 1] = '\0';

		if (strlen(input) == 0)
			continue;

		if (strcmp(input, "exit") == 0)
			break;

		words = split_string_to_words(input, separator);

		handle_shell_cmds(words, argv);
		free(input), free(words);
		input = NULL, words = NULL;
	}

	free(input), free(words);
	return (0);
}
