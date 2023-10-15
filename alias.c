#include "shell.h"
struct Alias aliases[MAX_ALIASES];
int aliasCount = 0;


/**
* parseAliasDefinition - Parses an alias definition into
* separate name and value.
* @definition: The alias definition string to parse.
* @name: A pointer to a pointer that will store the extracted alias name.
* @value: A pointer to a pointer that will store the extracted alias value.
*/
void parseAliasDefinition(const char *definition, char **name, char **value)
{

	*name = strdup(definition);
	*value = strchr(*name, '=');

	if (*value != NULL)
	{
		*(*value) = '\0';
		(*value)++;
	}
}
/**
* findAliasIndex - Finds the index of an alias in the aliases array by name.
* @name: The name of the alias to find.
* Return: The index of the alias if found; otherwise, -1.
*/
int findAliasIndex(const char *name)
{

	int j;

	for (j = 0; j < aliasCount; ++j)
	{
		if (strcmp(name, aliases[j].name) == 0)
		{
			return (j);
		}
	}
	return (-1);
}
/**
* updateAlias - Updates the value of an existing alias or adds a new alias.
* @name: The name of the alias.
* @value: The value to set for the alias.
*/
void updateAlias(const char *name, const char *value)
{
	int aliasIndex = findAliasIndex(name);

	if (aliasIndex != -1)
	{
		fflush(stdout);
		strcpy(aliases[aliasIndex].value, value);
	}
	else
	{
		if (aliasCount < MAX_ALIASES)
		{
			strcpy(aliases[aliasCount].name, name);
			strcpy(aliases[aliasCount].value, value);
			aliasCount++;
		}
		else
		{
			fprintf(stderr, "Error: Maximum number of aliases reached.\n");
			fflush(stderr);
		}
	}
}
/**
* defineAliases - Defines aliases based on an array of alias definitions.
* @definitions: An array of alias definitions.
* @definitionCount: The number of elements in the 'definitions' array.
*/
void defineAliases(char *definitions[], int definitionCount)
{
	int i;

	for (i = 0; i < definitionCount; ++i)
	{
		char *name, *value;

		parseAliasDefinition(definitions[i], &name, &value);

		if (value == NULL)
		{
			fprintf(stderr, "Invalid alias definition: %s\n", definitions[i]);
			fflush(stderr);
			free(name);
			continue;
			}

		updateAlias(name, value);
		free(name);
	}
}

/**
* handleAliasCommand - Handles the 'alias' shell command.
* @args: An array of arguments passed to the 'alias' command.
* Return: 0 on success, -1 on error.
*/
int handleAliasCommand(char *args[])
{
	int i, argCount = 0;
	char *copyArgs[MAX_ALIASES];

	while (args[argCount] != NULL)
	{
		copyArgs[argCount] = strdup(args[argCount]);
		argCount++;
	}
	copyArgs[argCount] = NULL;

	if (copyArgs[1] == NULL)
	printAliases();
	else if (strchr(copyArgs[1], '=') != NULL)
	{
		int definitionCount = 0;
		int i;
		char *definitions[MAX_ALIASES];

		for (i = 1; copyArgs[i] != NULL; ++i)
		{
			definitions[definitionCount] = copyArgs[i];
			definitionCount++;
		}
		defineAliases(definitions, definitionCount);
	}
	else
	{
		int nameCount = 0;
		char *names[MAX_ALIASES];

		for (i = 1; copyArgs[i] != NULL; ++i)
		{
			names[nameCount] = copyArgs[i];
			nameCount++;
		}
		printSpecificAliases(names, nameCount);
	}
	for (i = 0; i < argCount; ++i)
		free(copyArgs[i]);
	return (0);
}
