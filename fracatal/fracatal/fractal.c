/*
** EPITECH PROJECT, 2023
** fracatal
** File description:
** fractal.c
*/

#include "my.h"

char **remp(char **fract, char **arr, int *l, int *c)
{
    int li = 0;
    int ci = 0;
    int co = *c;
    int lo = *l;

    for (li = 0; arr[li] != NULL; li++) {
        co = *c;
        for (ci = 0; arr[li][ci]  != '\0'; ci++) {
            fract[lo][co] = arr[li][ci];
            co++;
        }
        fract[lo][co] = '\0';
        lo++;
    }
    *c = co;
    *l = lo;
    return fract;
}

char **fractal(char *str, char **arr1, char **arr2)
{
    int line = count(str, '@') * nb_str_in_array(arr1);
    int cols = count_dot_diez(str) * strlen(arr1[0]);
    int l = 0;
    int c = 0;
    int k = 0;
    char **fract = malloc((line + 1) * sizeof(char *));

    for (int a = 0; a < line; a++)
        fract[a] = malloc((cols + 1) * sizeof(char));
    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] == '@') {
            c = 0;
            k = l;
            continue;
        }
        l = k;
        if (str[a] == '.')
            remp(fract, arr2, &l, &c);
        if (str[a] == '#')
            remp(fract, arr1, &l, &c);
    }
    fract[l] = NULL;
    return fract;
}