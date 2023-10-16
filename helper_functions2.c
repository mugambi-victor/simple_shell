#include"shell.h"
/**
 * handleComments - Removes comments from a line by truncating at the '#' character.
 * @line: The input line containing a possible comment.
 *
 * This function checks if the input line contains a '#' character, indicating a comment.
 * If a comment is found, it truncates the line at the '#' character, effectively removing
 * the comment and ensuring only the relevant part of the line is retained.
 */
void handleComments(char *line)
{
	 char *commentPos;
if (line == NULL)
{
return;
}

commentPos = strchr(line, '#');
if (commentPos != NULL)
{
if (commentPos == line || *(commentPos - 1) == ' ')
{
*commentPos = '\0';
}
}
}



/**
 * _strstr - Locates the first occurrence of a substring in a string.
 * @haystack: The string to search within.
 * @needle: The substring to search for.
 *
 * Return: If the substring is found, a pointer to the beginning of the
 *         first occurrence is returned. If the substring is not found,
 *         NULL is returned.
 */
char *_strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
	{
		return ((char *)haystack);
	}

	while (*haystack != '\0')
	{
		const char *h = haystack;
		const char *n = needle;

		while (*n != '\0' && *h == *n)
		{
			h++;
			n++;
		}

		if (*n == '\0')
		{
			return ((char *)haystack);
		}

		haystack++;
	}

	return (NULL);
}

/**
 * _strcat - Concatenate two strings.
 * @str1: The first string.
 * @str2: The second string to append to the first.
 *
 * Return: A newly allocated string containing the concatenated result.
 *         The caller is responsible for freeing the memory.
 */
char *_strcat(const char *str1, const char *str2)
{
	size_t len1 = _strlen(str1);
	size_t len2 = _strlen(str2);
	size_t totallen = len1 + len2;

	char *result = (char *)malloc(totallen + 1);

	if (result == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	_strcpy(result, str1);
	_strcpy(result + len1, str2);
	return (result);
}
