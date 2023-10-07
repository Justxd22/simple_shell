#include "shell.h"

/**
 *interactive_mode-function that interacte directly with the user
 @argc: is the number of arguments
 @argv: is an array of arguments
 */
int interactive_mode() {
    char *line;
    int status;

    while (1) {
        printf("($)");
        line = read_the_given_line(); // Function to read the given input
        if (line == NULL)
            break;
        status = process_the_given_input(line); // Function to process, parse, and execute given input
        free(line);
    }
    return 0;
}

/**
 *non_interactive_mode-function that interacts with commands
 @argc: is the number of arguments
 @argv: is an array of arguments
 */
int non_interactive_mode(int argc, char *argv[]) {
    char *line;
    int status;

    if (argc > 1) {
        FILE *script = fopen(argv[1], "r");
        if (script == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        while ((line = read_the_given_input(script)) != NULL) {
            status = process_the_given_input(line);
            free(line);
        }
        fclose(script);
    }
    return 0;
}

/**
 *main-it's the main function
 @argc: is the number of arguments
 @argv: is an array of arguments
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Interactive mode
        return interactive_mode();
    } else {
        // Non-interactive mode
        return non_interactive_mode(argc, argv);
    }
}
