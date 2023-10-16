#include "shell.h"
#include <limits.h>
/**
 * handleBuiltInCommands - Handles built-in commands.
 * @programName: The name of the program.
 * @command: The command being executed.
 * @args: An array of command arguments.
 * @environ: The environment variables.
 *
 * Returns:
 *    - 0 if the command is NULL or not a built-in command.
 *    - The exit status of the executed built-in command.
 */
int handleBuiltInCommands(
char *command, char *args[], char **environ)
{
	int exitStatus;

	if (command == NULL)
		return (0);
	if (_strcmp(command, "env") == 0)
	{
		exitStatus = handleEnvCommand(environ);
		setExitStatus(exitStatus);
		return (exitStatus);
	}
	else if (_strcmp(command, "setenv") == 0)
		return (handleSetenvCommand(args));
	else if (_strcmp(command, "unsetenv") == 0)
		return (handleUnsetenvCommand(args));
	else if (_strcmp(command, "cd") == 0)
	{
		handleCdCommand(args);
		return (0);
	}
		else if (_strcmp(command, "alias") == 0)
		return (handleAliasCommand(args));
	return (1);
}
