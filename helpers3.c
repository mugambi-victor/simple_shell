#include "shell.h"

void executeCommandsSeparatedBySemicolon(char *programName ,char *line, bool interactive) 
{
int numCommands;
char **commands;
int i;

splitCommandsWithSemiColon(line, &commands, &numCommands);
executeCommands(programName, commands, numCommands, interactive);

for (i = 0; i < numCommands; i++) {
free(commands[i]);
}
free(commands);
}

void executeCommandsSeparatedByLogicalOr(char *programName, char *line, bool interactive) {
int numSubcommands, i;
char **subcommands;
splitCommandsWithLogicalOr(line, &subcommands, &numSubcommands);

executeCommands(programName, subcommands, 1, interactive);

if (lastCommandStatus != 0 && numSubcommands > 1)
{
executeCommands(programName, subcommands + 1, numSubcommands - 1, interactive);
}

for (i= 0; i < numSubcommands; i++)
{
free(subcommands[i]);
}
free(subcommands);
}

void executeCommandsSeparatedByLogicalAnd(char *programName, char *line, bool interactive) {
int numSubcommands , i;
char **subcommands;
splitCommandsWithLogicalAnd(line, &subcommands, &numSubcommands);

executeCommands(programName, subcommands, 1, interactive);

if (lastCommandStatus == 0 && numSubcommands > 1)
{
executeCommands(programName, subcommands + 1, numSubcommands - 1, interactive);
}

for (i = 0; i < numSubcommands; i++) {
free(subcommands[i]);
}
free(subcommands);
   
}
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
return false;
}

for (i = 0; i < r; i++) {
if ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n')
{
break;
}
}

if (i == r) 
{
       
return false; 
}

handleComments(*line);

if (r > 0 && (*line)[r - 1] == '\n')
{
(*line)[r - 1] = '\0';
}

return true;
}


void handleNormalCommand(char *programName, char *line, bool interactive) 
{
int numCommands = 1;
char *commands[1];
commands[0] = strdup(line);
executeCommands(programName, commands, numCommands, interactive);
free(commands[0]);
}
