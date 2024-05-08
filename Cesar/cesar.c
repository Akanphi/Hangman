/*
** EPITECH PROJECT, 2024
** cvbn,;
** File description:
**  b
*/

#include "my.h"

char verif_alph(char c, int key, char a, char z)
{
    if ((c + key) >= a && (c + key) <= z)
        return (c + key);
    else {
        if ((c + key) < a)
            return (c + key + 26);
        if ((c + key) > z)
            return (c + key - 26);
    }
}

char *cesar(char *str, int key)
{
    char *src = malloc((strlen(str) + 1) * sizeof(char));
    int a = 0;

    for (a = 0; str[a] != '\0'; a++) {
        if (str[a] >= 'A' && str[a] <= 'Z') {
            src[a] = verif_alph(str[a], key, 'A', 'Z');
            continue;
        }
        if (str[a] >= 'a' && str[a] <= 'z') {
            src[a] = verif_alph(str[a], key, 'a', 'z');
            continue;
        }
        if (str[a] >= '0' && str[a] <= '9') {
            src[a] = verif_alph(str[a], key, '0', '9');
            continue;
        }
        src[a] = str[a];
    }
    src[a] = '\0';
    return src;
}
