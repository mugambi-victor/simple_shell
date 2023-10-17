#include "shell.h"

/**
 * handleExitCommand - Handles the 'exit' command.
 * @programName: The name of the program.
 * @command: The command that is being executed.
 * @args: An array of command arguments.
 *
 * Returns:
 *  - 0 on success.
 *  - 2 if an illegal number is provided as an argument.
 */


/**
 * handleEnvCommand - Handles the 'env' command.
 * @environ: The environment variables.
 *
 * Returns: 0 on success.
 */
int handleEnvCommand(char **environ)
{
	char **envVar = environ;

	while (*envVar != NULL)
	{
		const char *envString = *envVar;
		size_t envStringLength = _strlen(envString);

		write(1, envString, envStringLength);
		write(1, "\n", 1);
		envVar++;
	}
	return (0);
}
/**
 * handleSetenvCommand - Handles the 'setenv' command.
 * @args: An array of command arguments.
 *
 * Returns:
 *  - 0 on success.
 *  - 1 on failure to set an environment variable.
 */
int handleSetenvCommand(char *args[])
{
	if (args[1] != NULL && args[2] != NULL)
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			custom_fprintf(stderr, "Failed to set environment variable: %s\n", args[1]);
			fflush(stderr);
			setExitStatus(1);
			return (1);
		}
	}
	else
	{
		custom_fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		fflush(stderr);
		setExitStatus(1);
		return (1);
	}
	return (0);
}
/**
 * handleUnsetenvCommand - Handles the 'unsetenv' command.
 * @args: An array of command arguments.
 *
 * Returns:
 *  - 0 on success.
 *  - 1 on failure to unset an environment variable.
 */
int handleUnsetenvCommand(char *args[])
{
	if (args[1] != NULL)
	{
		if (unsetenv(args[1]) != 0)
		{
			custom_fprintf(stderr, "Failed to unset environment variable: %s\n", args[1]);
			fflush(stderr);
			setExitStatus(1);
			return (1);
		}
	}
	else
	{
		custom_fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		fflush(stderr);
		setExitStatus(1);
		return (1);
	}
	return (0);
}
/**
 * handleCdCommand - Handles the 'cd' command.
 * @args: An array of command arguments.
 *
 * Returns:
 *  - 0 on success.
 *  - 1 on failure to change the directory.
 */

int handleCdCommand(char *args[])
{
char *targetDirectory;
char currentDirectory[4096];
char *newPWD;

if (getenv("OLDPWD") == NULL)
{
if (getcwd(currentDirectory, sizeof(currentDirectory)) == NULL)
{
perror("getcwd");
return (1);
}

if (setenv("OLDPWD", currentDirectory, 1) != 0)
{
perror("setenv OLDPWD");
return (1);
		}
}

if (args[1] != NULL)
{
if (_strcmp(args[1], "-") == 0)
{
targetDirectory = getenv("OLDPWD");
if (targetDirectory == NULL)
{
custom_fprintf(stderr, "OLDPWD environment variable not set.\n");
fflush(stderr);
setExitStatus(1);
return (1);
}
}
else{
targetDirectory = args[1];
}
}
else{
targetDirectory = getenv("HOME");
}

if (getcwd(currentDirectory, sizeof(currentDirectory)) == NULL)
{
perror("getcwd");
return (1);
}

if (chdir(targetDirectory) == -1)
{
custom_fprintf(stderr, "../hsh: 1: cd: can't cd to %s\n", targetDirectory);
setExitStatus(0);
return (0);
}

newPWD = getcwd(NULL, 0);

if (newPWD == NULL)
{
perror("getcwd");
return (1);
}

if (setenv("PWD", newPWD, 1) != 0)
{
perror("setenv PWD");
free(newPWD);
return (1);
}

free(newPWD);

if (setenv("OLDPWD", currentDirectory, 1) != 0)
{
perror("setenv OLDPWD");
return (1);
}

if (args[1] != NULL && _strcmp(args[1], "-") == 0)
{
printf("%s\n", getenv("PWD"));
}

setExitStatus(0);
return (0);
}