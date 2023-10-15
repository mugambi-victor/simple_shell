#include "shell.h"
int lastCommandStatus = 0;

void setExitStatus(int status)
{
	lastCommandStatus = status;
}

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
		if (_strchr(line, ';') != NULL)
		{
			executeCommandsSeparatedBySemicolon(argv[0], line, interactive);
		}
		else if (_strstr(line, "||") != NULL)
		{
			executeCommandsSeparatedByLogicalOr(argv[0], line, interactive);
		}
		else if (_strstr(line, "&&") != NULL)
		{
			executeCommandsSeparatedByLogicalAnd(argv[0], line, interactive);
		}
		else if (strstr(line, "exit"))
		{
			char *command;
			char *args[2];
			int i;

			splitCommand(line, &command, args);
			handleExitCommand(argv[0], line, command, args);
			free(command);
			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
		}
		else
		{
			handleNormalCommand(argv[0], line, interactive);
		}
		free(line);
		line = NULL;
		len = 0;
	}
	free(line);
	return (0);
}


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
	}
}

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

int isNumeric(const char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}
