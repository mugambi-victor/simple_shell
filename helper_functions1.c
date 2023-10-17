#include "shell.h"

/**
 * splitCommand - Splits the input line into a command and its arguments.
 * @line: The input line to be split.
 * @command: Pointer to store the extracted command.
 * @args: Array to store the extracted arguments.
 *
 * This function uses _strtok to tokenize the input line and extracts the
 * command and its arguments. Memory is dynamically allocated for the command
 * and arguments, and it should be freed after use.
 */
void splitCommand(char *line, char **command, char *args[])
{
char *token = strtok(line, " ");
int i = 0;


if (token == NULL)
{

*command = NULL;
args[0] = NULL;
return;
}

*command = strdup(token);

while (token != NULL)
{
args[i] = strdup(token);
token = strtok(NULL, " ");
i++;
}
args[i] = NULL;

}
/**
 * splitCommandsWithSemiColon - Splits the
 * input line into commands using a semicolon as a delimiter.
 * @line: The input line to be split.
 * @commands: Pointer to an array to store the split commands.
 * @numCommands: Pointer to store the number of split commands.
 *
 * This function uses _strtok to tokenize the input line based on semicolons,
 * extracting individual commands. Memory is dynamically allocated for each
 * command, and the array should be freed after use.
 */
void splitCommandsWithSemiColon(char *line, char ***commands, int *numCommands)
{
int j, i;
char **tokens;
*numCommands = 0;

*commands = (char **)malloc(sizeof(char *) * 1024);

tokens = _strtok(line, ";");
i = 0;
while (tokens != NULL && tokens[i] != NULL)
{
(*commands)[(*numCommands)++] = strdup(tokens[i]);
i++;
}

for (j = 0; tokens[j] != NULL; j++)
{
free(tokens[j]);
}
free(tokens);
}

/**
 * splitCommandsWithLogicalOr - Splits the input
 * line into commands using logical OR (||) as a delimiter.
 * @line: The input line to be split.
 * @subcommands: Pointer to an array to store the split subcommands.
 * @numSubcommands: Pointer to store the number of split subcommands.
 *
 * This function uses _strtok to tokenize the input line based on logical OR,
 * extracting individual subcommands. Memory is dynamically allocated for each
 * subcommand, and the array should be freed after use.
 */

void splitCommandsWithLogicalOr(char *line, char ***subcommands, int *numSubcommands)
{
int j, i;
char **tokens;
*numSubcommands = 0;

*subcommands = (char **)malloc(sizeof(char *) * 1024);

tokens = _strtok(line, "||");
i = 0;
while (tokens != NULL && tokens[i] != NULL)
{
(*subcommands)[(*numSubcommands)++] = strdup(tokens[i]);
i++;
}
for (j = 0; tokens[j] != NULL; j++)
{
free(tokens[j]);
}
free(tokens);
}

/**
 * splitCommandsWithLogicalAnd - Splits the input line into commands using logical AND (&&) as a delimiter.
 * @line: The input line to be split.
 * @subcommands: Pointer to an array to store the split subcommands.
 * @numSubcommands: Pointer to store the number of split subcommands.
 *
 * This function uses _strtok to tokenize the input line based on logical AND,
 * extracting individual subcommands. Memory is dynamically allocated for each
 * subcommand, and the array should be freed after use.
 */

void splitCommandsWithLogicalAnd(char *line, char ***subcommands, int *numSubcommands)
{
char **tokens;
int j, i;
*numSubcommands = 0;

*subcommands = (char **)malloc(sizeof(char *) * 1024);

tokens = _strtok(line, "&&");
i = 0;
while (tokens != NULL && tokens[i] != NULL)
{
(*subcommands)[(*numSubcommands)++] = strdup(tokens[i]);
i++;
}
for (j = 0; tokens[j] != NULL; j++)
{
free(tokens[j]);
}
free(tokens);
}


/**
 * executeCommandsFromFile - Executes commands from a file.
 * @programName: The name of the program.
 * @filename: The name of the file containing commands.
 *
 * This function reads commands from the specified file, one line at a time,
 * and executes them using the executeCommands function.
 */
void executeCommandsFromFile(char *programName, char *filename)
{
char *line;
int numCommands;
size_t len;
ssize_t read;
char *commands[1];
FILE *file = fopen(filename, "r");
if (file == NULL)
{
fprintf(stderr, "%s: 0: cannot open %s: No such file\n", programName, filename);
lastCommandStatus = 2;
exit(lastCommandStatus);
}

line = NULL;
len = 0;

while ((read = getline(&line, &len, file)) != -1)
{
if (line[read - 1] == '\n')
{
line[read - 1] = '\0';
}
numCommands = 1;

commands[0] = strdup(line);
executeCommands(programName, commands, numCommands, false);
free(commands[0]);
}

free(line);
fclose(file);
}
