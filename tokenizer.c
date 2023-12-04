#include "shell.h"

/**
 * split_string - helper function to split a string into words
 * @str: the input string
 * @d: the delimiter
 * @numwords: pointer to store the number of words
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
static char **split_string(const char *str, const char *d, int *numwords)
{
	int i, j, k, m;
	char **s;

	if (str == NULL || str[0] == '\0')
		return NULL;

	if (!d)
		d = " ";

	*numwords = 0;
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			(*numwords)++;

	if (*numwords == 0)
		return NULL;

	s = malloc((1 + *numwords) * sizeof(char *));
	if (!s)
		return NULL;

	for (i = 0, j = 0; j < *numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return NULL;
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL;
	return s;
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(const char *str, const char *d)
{
	int numwords;
	return split_string(str, d, &numwords);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(const char *str, char d)
{
	int numwords;
	return split_string(str, &d, &numwords);
}
