#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

extern char **environ;
extern int lastCommandStatus;

#include <ctype.h>

#define MAX_ALIASES 100
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100

struct Alias {
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
};

extern struct Alias aliases[];
extern int aliasCount;

void splitCommand(char *line, char **command, char *args[]);
int handleBuiltInCommands( char *command, char *args[], char **environ);
void setExitStatus(int status);
int custom_fprintf(FILE *stream, const char *format, ...);

int handleEnvCommand(char **environ);
void executeCommandWithAbsolutePath( char *command, char *args[], bool interactive);
void executeCommandWithNoAbsolutePath(char *programName, char *command, char *args[]);
void executeCommands(char *programName, char *commands[], int numCommands, bool interactive);

void splitCommandsWithSemiColon(char *line, char ***commands, int *numCommands) ;
void executeCommandsWithOr(char *commands[], int numCommands, bool interactive);

void executeCommandsWithLogicalOr(char *subcommands[], int numSubcommands, bool interactive);
void splitCommandsWithLogicalOr(char *command, char ***subcommands, int *numSubcommands);
void splitCommandsWithLogicalAnd(char *line, char ***subcommands, int *numSubcommands);
void replaceVariables(char **args);
void handleComments(char *line);
void executeCommandsFromFile(char *programName, char *filename);


char **_strtok(char *strr, char *delim);

void executeCommandsSeparatedBySemicolon(char *programName ,char *line, bool interactive);
void executeCommandsSeparatedByLogicalOr(char *programName ,char *line, bool interactive);
void executeCommandsSeparatedByLogicalAnd(char *programName ,char *line, bool interactive);
void handleNormalCommand(char *programName, char *line, bool interactive);
bool readLine(char **line, size_t *len, int *lastCommandStatus) ;

int handleCdCommand(char *args[]);
int handleUnsetenvCommand(char *args[]);
int handleSetenvCommand(char *args[]);
int handleExitCommand(char *programName, char *fullLine, char *command, char *args[]);

int _strcmp(const char *str1, const char *str2);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strchr(const char *str, int c);
char *_strdup(const char *str);
char *_strstr(const char *haystack, const char *needle);
ssize_t get_line(char **lineptr, size_t *n, FILE *str);
int isNumeric(const char *str);

char *_strncpy(char *dest, const char *src, size_t n);
int handleAliasCommand(char *args[]);
void parseAliasDefinition(const char *definition, char **name, char **value);
int findAliasIndex(const char *name);
void updateAlias(const char *name, const char *value);
void defineAliases(char *definitions[], int definitionCount);
void printAliases(void);
void printSpecificAliases(char *names[], int nameCount);

void executeFileMode(char *programName, char *fileName);
void displayPrompt(bool interactive) ;
void processInput(char *programName, char *line, bool interactive);
void handleExit(char *programName, char *line);
void cleanupMemory(char *line);
int wordCounter(char *inputstr, char *delim);

#endif
