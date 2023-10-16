#include "shell.h"
/**
* printAliases - Prints all defined aliases in the format 'name='value''.
*/
void printAliases(void)
{
	int i;

	for (i = 0; i < aliasCount; ++i)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}
/**
* printSpecificAliases - Prints the values of
* specific aliases given their names.
* @names: An array of alias names to print.
* @nameCount: The number of elements in the 'names' array.
*/
void printSpecificAliases(char *names[], int nameCount)
{

	int i, j;

	for (i = 0; i < nameCount; ++i)
	{
		for (j = 0; j < aliasCount; ++j)
		{
			if (strcmp(names[i], aliases[j].name) == 0)
			{
				printf("%s='%s'\n", aliases[j].name, aliases[j].value);
				break;
			}
		}
	}
}
/**
 * isNumeric - Check if a given string represents a numeric value.
 * @str: The string to be checked.
 *
 * This function iterates through the characters
 * in the input string and returns
 * 1 if all characters are numeric digits (0-9),
 * indicating that the string is numeric.
 * Otherwise, it returns 0.
 *
 * Return: 1 if the string is numeric, 0 otherwise.
 */
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
