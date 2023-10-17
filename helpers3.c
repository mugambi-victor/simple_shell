#include "shell.h"
/**
 * executeCommandsSeparatedBySemicolon - Execute commands separated by semicolons
 *
 * @programName: Name of the program
 * @line: Input line containing commands separated by semicolons
 * @interactive: Flag indicating interactive mode
 */
void executeCommandsSeparatedBySemicolon(char *programName, char *line, bool interactive)
{
	int numCommands;
	char **commands;
	int i;

	splitCommandsWithSemiColon(line, &commands, &numCommands);
	executeCommands(programName, commands, numCommands, interactive);
	for (i = 0; i < numCommands; i++)
	{
		free(commands[i]);
	}
	free(commands);
}
/**
 * executeCommandsSeparatedByLogicalOr - Execute commands separated by logical OR
 *
 * @programName: Name of the program
 * @line: Input line containing commands separated by logical OR
 * @interactive: Flag indicating interactive mode
 */
void executeCommandsSeparatedByLogicalOr(char *programName, char *line, bool interactive)
{
	int numSubcommands, i;
	char **subcommands;

	splitCommandsWithLogicalOr(line, &subcommands, &numSubcommands);
	executeCommands(programName, subcommands, 1, interactive);
	if (lastCommandStatus != 0 && numSubcommands > 1)
	{
		executeCommands(programName, subcommands + 1, numSubcommands - 1, interactive);
	}
	for (i = 0; i < numSubcommands; i++)
	{
		free(subcommands[i]);
	}
	free(subcommands);
}
/**
 * executeCommandsSeparatedByLogicalAnd - Execute commands separated by logical AND
 *
 * @programName: Name of the program
 * @line: Input line containing commands separated by logical AND
 * @interactive: Flag indicating interactive mode
 */
void executeCommandsSeparatedByLogicalAnd(char *programName, char *line, bool interactive)
{
	int numSubcommands, i;
	char **subcommands;

	splitCommandsWithLogicalAnd(line, &subcommands, &numSubcommands);
	executeCommands(programName, subcommands, 1, interactive);
	if (lastCommandStatus == 0 && numSubcommands > 1)
	{
		executeCommands(programName, subcommands + 1, numSubcommands - 1, interactive);
	}
	for (i = 0; i < numSubcommands; i++)
	{
		free(subcommands[i]);
	}
	free(subcommands);
}
/**
 * readLine - Read a line from standard input and handle special cases
 *
 * @line: Pointer to the buffer to store the input line
 * @len: Pointer to the size of the buffer
 * @lastCommandStatus: Pointer to the status of the last command executed
 *
 * Returns true if a line is successfully read, false otherwise
 */
bool readLine(char **line, size_t *len, int *lastCommandStatus)
{
	ssize_t r;
	int i;
	r = getline(line, len, stdin);

	if (r == -1)
	{
		free(*line);
		if (feof(stdin))
		{
			exit(*lastCommandStatus);
		}
		return (false);
	}
	for (i = 0; i < r; i++)
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n')
		{
			break;
		}
	}
	if (i == r)
	{
		return (false);
	}
	handleComments(*line);
	if (r > 0 && (*line)[r - 1] == '\n')
	{
		(*line)[r - 1] = '\0';
	}
	return (true);
}
/**
 * handleNormalCommand - Handle a normal command line
 *
 * @programName: Name of the program
 * @line: Input line containing a single command
 * @interactive: Flag indicating interactive mode
 */
void handleNormalCommand(char *programName, char *line, bool interactive)
{
	int numCommands = 1;
	char *commands[1];
	commands[0] = strdup(line);

	executeCommands(programName, commands, numCommands, interactive);
	free(commands[0]);
}
