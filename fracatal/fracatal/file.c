/*
** EPITECH PROJECT, 2023
** fracatal
** File description:
** file.c
*/

#include "my.h"

int count(char *str, char c)
{
    int i = 0;

    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] == c)
            i++;
    }
    return i + 1;
}

int count_dot_diez(char *str)
{
    int n = 0;

    for (int a = 0; str[a] != '\0'; a++)
        if (str[a] == '.' || str[a] == '#')
            n++;
    return n;
}

int nb_str_in_array(char **arr)
{
    int a = 0;

    for (a = 0; arr[a] != NULL; a++);
    return a;
}

char **str_to_array(char *str, char *sep)
{
    char *src = strdup(str);
    int a = 0;
    char **arr = malloc((count(str, sep[0]) + 1) * sizeof(char *));
    char *tok = strtok(src, sep);

    for (a = 0; tok != NULL; a++) {
        arr[a] = strdup(tok);
        tok = strtok(NULL, sep);
    }
    arr[a] = NULL;
    free(src);
    return arr;
}
