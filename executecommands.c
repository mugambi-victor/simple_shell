#include "shell.h"

/**
 * findCommandPath - Finds the absolute path of a command in the system's PATH.
 * @command: The command to search for.
 * Returns:
 *   - A dynamically allocated string
 * containing the absolute path of the command.
 * Return - NULL if the command is not found in the PATH.
 */
char *findCommandPath(const char *command)
{
	int i, j;
	char *s;
	char *path = getenv("PATH");

	if (path != NULL)
	{
		char **tokens = _strtok(path, ":");

		if (tokens != NULL)
		{
			for (i = 0; tokens[i] != NULL; i++)
			{
				char executablePath[1024];

				_strcpy(executablePath, tokens[i]);
				strcat(executablePath, "/");
				strcat(executablePath, command);
				if (access(executablePath, X_OK) == 0)
				{
					s = _strdup(executablePath);

					for (j = 0; tokens[j] != NULL; j++)
					{
						free(tokens[j]);
					}
					free(tokens);
					return (s);
				}
			}
			for (i = 0; tokens[i] != NULL; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
		}
	}
	return (NULL);
}
/**
 * executeCommandWithAbsolutePath - Executes a command with an absolute path.
 * @command: The command to execute.
 * @args: An array of command arguments.
 * @interactive: A boolean flag indicating whether the execution is interactive.
 *
 * This function forks a child process and executes the specified command.
 */
void executeCommandWithAbsolutePath(char *command, char *args[], bool interactive)
{
	pid_t pid;

	replaceVariables(args);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			exit(127);
		}
		exit(0);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			if (interactive)
			{
				setExitStatus(2);
			}
			else
			{
				setExitStatus(2);
			}
		}
	}
}
/**
 * executeCommandWithNoAbsolutePath - Executes a command without an absolute path.
 * @programName: The name of the program.
 * @command: The command to execute.
 * @args: An array of command arguments.
 *
 * This function finds the absolute path of the command and then executes it.
 */
void executeCommandWithNoAbsolutePath(char *programName, char *command, char *args[])
{
	char *commandPath;

	replaceVariables(args);
	commandPath = findCommandPath(command);
	if (commandPath != NULL)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			if (execve(commandPath, args, environ) == -1)
			{
				perror("execve");
				setExitStatus(127);
			}
			exit(0);
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", programName, command);
				fflush(stderr);
				setExitStatus(127);
			}
		}
		free(commandPath);
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", programName, command);
		fflush(stderr);
		setExitStatus(127);
	}
}
/**
 * executeCommands - Executes multiple commands sequentially.
 * @programName: The name of the program.
 * @commands: An array of command strings.
 * @numCommands: The number of commands in the array.
 * @interactive: A boolean flag indicating whether the execution is interactive.
 *
 * This function iterates through the array of commands, executes each one,
 * and handles built-in commands separately.
 */
void executeCommands(char *programName, char *commands[], int numCommands, bool interactive)
{
	int i, j, k, builtInStatus, isAlias;

	for (i = 0; i < numCommands; i++)
	{
		char *command;
		char *args[1024];

		splitCommand(commands[i], &command, args);

		do {
			isAlias = 0;

			for (k = 0; k < aliasCount; ++k)
			{
				if (strcmp(command, aliases[k].name) == 0)
				{
					free(command);
					command = strdup(aliases[k].value);
					isAlias = 1;
					break;
				}
			}
		} while (isAlias);
		builtInStatus = handleBuiltInCommands(command, args, environ);

		if (builtInStatus != 1)
		{
			setExitStatus(builtInStatus);
		}
		else if (command[0] == '/')
		{
			executeCommandWithAbsolutePath(command, args, interactive);
		}
		else
		{
			executeCommandWithNoAbsolutePath(programName, command, args);
		}
		free(command);
		for (j = 0; args[j] != NULL; j++)
		{
			free(args[j]);
		}
	}
}
