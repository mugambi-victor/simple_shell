#include "shell.h"
int lastCommandStatus = 0;
/**
 * setExitStatus - Set the exit status of the last command.
 * @status: The exit status to be set.
 *
 * This function updates the global variable
 * lastCommandStatus with the provided exit status.
 * It allows other parts of the program to
 * access and utilize the exit status of the most recent command.
 *
 * Return: void
 */
void setExitStatus(int status)
{
	lastCommandStatus = status;
}
/**
 * main - Entry point of the shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * This function handles the main flow of the
 * shell program, processing commands either from
 * the command line or from a file.
 * It continuously prompts the user for input in interactive mode.
 *
 * Return: The exit status of the last command.
 */
int main(int argc, char *argv[])
{
	char *line = NULL;

	bool interactive;
	size_t len = 0;

	if (argc == 2)
	{
		/**
		* Running in file mode
		*/
		executeCommandsFromFile(argv[0], argv[1]);
		return (lastCommandStatus);
	}
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
		{
			printf("$ ");
			fflush(stdout);
		}
		if (!readLine(&line, &len, &lastCommandStatus))
		{
			continue;
		}
		processInput(argv[0], line, interactive);
		free(line);
		line = NULL;
		len = 0;
	}
	free(line);
	return (0);
}
/**
 * processInput - Process the user input
 * and execute the corresponding command.
 * @programName: The name of the program (argv[0]).
 * @line: The input line from the user.
 * @interactive: Flag indicating whether the shell is in interactive mode.
 *
 * This function analyzes the user input and
 * executes the appropriate command or
 * handles special cases like exit or variable replacement.
 *
 * Return: void
 */
void processInput(char *programName, char *line, bool interactive)
{
	if (_strchr(line, ';') != NULL)
	{
		executeCommandsSeparatedBySemicolon(programName, line, interactive);
	}
	else if (_strstr(line, "||") != NULL)
	{
		executeCommandsSeparatedByLogicalOr(programName, line, interactive);
	}
	else if (_strstr(line, "&&") != NULL)
	{
		executeCommandsSeparatedByLogicalAnd(programName, line, interactive);
	}
	else if (strstr(line, "exit"))
	{
		char *command;
		char *args[2];
		int i;

		splitCommand(line, &command, args);
		handleExitCommand(programName, line, command, args);
		free(command);
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
	}
	else
	{
		handleNormalCommand(programName, line, interactive);
	}
}
/**
 * replaceVariables - Replace special
 * variables in the command arguments.
 * @args: Array of command arguments.
 *
 * This function replaces special variables
 * like "$?" and "$$" in the command arguments
 * with their corresponding values (exit status and process ID).
 *
 * Return: void
 */
void replaceVariables(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		if (_strcmp(args[i], "$?") == 0)
		{
			char statusStr[12];

			snprintf(statusStr, sizeof(statusStr), "%d", lastCommandStatus);
			free(args[i]);
			args[i] = _strdup(statusStr);
		}
		else if (_strcmp(args[i], "$$") == 0)
		{
			char pidStr[12];

			snprintf(pidStr, sizeof(pidStr), "%d", getpid());
			free(args[i]);
			args[i] = _strdup(pidStr);
		}
		else if (args[i][0] == '$' && args[i][1] != '\0')
		{
			char *envVarValue = getenv(args[i] + 1);

			if (envVarValue != NULL)
			{
				free(args[i]);
				args[i] = _strdup(envVarValue);
			}
			else
			{
				free(args[i]);
				args[i] = NULL;
			}
		}
	}
}
/**
 * handleExitCommand - Handle the exit command
 * and terminate the shell if necessary.
 * @programName: The name of the program (argv[0]).
 * @fullLine: The entire command line.
 * @command: The command part of the input.
 * @args: Array of command arguments.
 *
 * This function processes the exit command,
 * setting the exit status or terminating the shell
 * based on the provided exit code or the
 * exit status of the last command.
 *
 * Return: The exit status or an error code.
 */
int handleExitCommand(char *programName, char *fullLine, char *command, char *args[])
{
	int i, exitCode;

	if (args[1] != NULL && !isNumeric(args[1]))
	{
		fprintf(stderr, "%s: 1: %s: Illegal number: %s\n", programName, command, args[1]);
		fflush(stderr);
		setExitStatus(2);
		return (2);
	}
	else if (args[1] != NULL)
	{
		exitCode = atoi(args[1]) % 256;

		if (exitCode >= 0 && exitCode <= 255)
		{
			free(command);
			command = NULL;

			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			free(fullLine);
			fullLine = NULL;

			setExitStatus(exitCode);
			exit(lastCommandStatus);
		}
		else
		{
			fprintf(stderr, "%s: 1: %s: Invalid number: %s\n", programName, command, args[1]);
			fflush(stderr);
			return (2);
		}
	}
	else
	{
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
		free(fullLine);
		free(command);
		command = NULL;

		exit(lastCommandStatus);
	}
}

