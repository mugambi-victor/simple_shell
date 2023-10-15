#include "shell.h"

/**
 * _strcmp - Custom string comparison function.
 *
 * @str1: A pointer to the first null-terminated string to compare.
 * @str2: A pointer to the second null-terminated string to compare.
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}

/**
 * _strlen - Calculate the length of a null-terminated string.
 *
 * @str: The input string.
 *
 * Return: The length of the string (excluding the null terminator).
 */
size_t _strlen(const char *str)
{
	const char *s = str;

	while (*s)
	{
		s++;
	}
	return (s - str);
}

/**
 * _strcpy - Copy a null-terminated string from source to destination.
 *
 * @dest: The destination buffer where the string will be copied.
 * @src: The source string to be copied.
 *
 * Return: A pointer to the beginning of the destination string (dest).
 */
char *_strcpy(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return (original_dest);
}

/**
 * _strchr - Custom character search function.
 *
 * @str: A pointer to the null-terminated string to search within.
 * @c: The character to search for.
 *
 * Return: A pointer to the first occurrence of 'c' in 'str', or NULL if 'c'
 *         is not found.
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strdup - Duplicate a null-terminated string.
 *
 * @str: The string to duplicate.
 *
 * Return: A pointer to a newly allocated duplicate string, or NULL on memory
 *         allocation failure.
 */
char *_strdup(const char *str)
{
	size_t len;
	char *duplicate;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str) + 1;
	duplicate = (char *)malloc(len);

	if (duplicate == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	_strcpy(duplicate, str);
	return (duplicate);
}
