#include "shell.h"


/**
 * handle_shell_cmds - takes cmds and execute them
 * @words: commands + their args to execute
 * @argv: argv to get program name
 * @path: sys path from env
 * Return: exit code
 */
int handle_shell_cmds(char **words, char *argv[], char *path)
{
	char *token = strtok(path, ":");
	char path_command[MAX_WORDS];
	int status;
	pid_t pid;

	if (path == NULL)
		printf("PATH environment variable not set\n");

	while (token != NULL)
	{
		sprintf(path_command, "%s%s%s", strchr(words[0], '/') == NULL ? token : "",
strchr(words[0], '/') == NULL ? "/" : "", words[0]);
		if (access(path_command, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				printf("ERROR FORK\n");
				exit(100);
			}
			else if (pid == 0)
			{
				if (execvp(path_command, words) == -1)
					break;
			}
			else
			{
				if (waitpid(pid, &status, 0) == -1)
				{
					printf("Error Child\n");
					exit(101);
				}
				if (WIFEXITED(status))
					return (WEXITSTATUS(status));
			}
		}
		token = strtok(NULL, ":");
	}
	printf("%s: No such file or directory\n", argv[0]);
	return (-1);
}


/**
 * print_env - print all env
 * no Return
 */
void print_env(void)
{
	char *envar = *environ;

	while (envar)
		printf("%s", envar), envar = *(environ++);
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
	char *separator = " ", *input = NULL, **words = NULL, *orip = getenv("PATH"),
*path = strdup(orip);
	int o = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");
		fflush(stdout), read_bytes = getline(&input, &input_size, stdin);
		if (strcmp(input, "env") == 0)
		{
			print_env();
			continue;
		}
		if (read_bytes == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		input[read_bytes - 1] = '\0';
		if (strlen(input) == 0)
			continue;

		words = split_string_to_words(input, separator);
		if (strcmp(words[0], "exit") == 0)
		{
			if (words[1])
				o = atoi(words[1]);
			break;
		}
		free(path), path = strdup(orip), o = handle_shell_cmds(words, argv, path);
		free(input), input = NULL, free(words), words = NULL;
	}

	free(input), free(words), free(path);
	return (o);
}
