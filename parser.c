#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *path)
{
    struct stat st;

    return path && !stat(path, &st) && (st.st_mode & S_IFREG);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    if (!pathstr || _strlen(cmd) > 2 || !starts_with(cmd, "./"))
    {
        if (is_cmd(cmd))
            return cmd;
    }

    while (*pathstr)
    {
        char *path = _strchr(pathstr, ':');
        if (!path)
            path = _strchr(pathstr, '\0');

        char *dir = dup_chars(pathstr, 0, path - pathstr);
        char *full_path = _strcat3(dir, "/", cmd);

        if (is_cmd(full_path))
        {
            free(dir);
            return full_path;
        }

        free(dir);
        pathstr = *path == '\0' ? path : path + 1;
    }

    return NULL;
}

/**
 * dup_chars - duplicates characters
 * @str: the string to duplicate
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *str, int start, int stop)
{
    char *result = malloc(stop - start + 1);
    if (!result)
        return NULL;

    _strncpy(result, str + start, stop - start);
    result[stop - start] = '\0';
    return result;
}
