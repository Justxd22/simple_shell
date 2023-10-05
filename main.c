#include "shell.h"


int main()
{
	char *input = NULL;
	size_t input_size = 0, read_bytes;
	char* delimiter = " ";
	char** words;
	int x = 0, status;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		read_bytes = getline(&input, &input_size, stdin);

		if (read_bytes == -1) {
			printf("\n");
			break;
		}

		input[read_bytes - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("\n");
			break;
		}

		words = split_string(input, delimiter);

		pid = fork();
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

		for (x = 0; words[x] != NULL; x++)
			printf("x%d : %s\n", x, words[x]);

		input = NULL;

	}

	free(words);

	return (0);
}
