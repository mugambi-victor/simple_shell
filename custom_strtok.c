#include "shell.h"


/**
 * wordCounter - Counts the number of words
 * in a inputstring using mul_iple delim
 * @inputstr: the input inputstring
 * @delim: a inputstring containing multiple delimiter characters
 * Return: the number of words
 */
int wordCounter(char *inputstr, char *delim)
{
	int numwords = 0;
	bool inWord = false;
	int i;

	for (i = 0; inputstr[i] != '\0'; i++)
	{
		if (_strchr(delim, inputstr[i]) != NULL)
		{
			if (inWord)
			{
				inWord = false;
				numwords++;
			}
		}
		else
		{
			if (!inWord)
				inWord = true;
		}
	}
	if (inWord)
		numwords++;

	return (numwords);
}

/**
 * _strtok - Splits a string into words using multiple delim
 * @strr: the input string
 * @delim: a string containing multiple delimiter characters
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtok(char *strr, char *delim)
{
	int i, j, k, numwords, m;
	char **s;

	if (strr == NULL || strr[0] == '\0'
|| delim == NULL || delim[0] == '\0')
		return (NULL);

	numwords = wordCounter(strr, delim);

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_strchr(delim, strr[i]) != NULL)
			i++;

		k = 0;
		while (_strchr(delim, strr[i + k]) == NULL && strr[i + k] != '\0')
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = strr[i++];

		s[j][k] = '\0';
	}

	s[j] = NULL;
	return (s);
}
