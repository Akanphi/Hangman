/*
** EPITECH PROJECT, 2024
** minicut.c
** File description:
** minicut functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 10000

typedef struct minicut
{
    int c_activate;
    int d_activate;
    int f_activate;
    char *positions;
    char *delim;
} cut_t;


int my_putstr(char *str)
{
    while (*str) {
        write(1, str, 1);
        *str++;
    }
    return 0;
}

int free_struct(cut_t *cut)
{
    if (cut->positions != NULL)
        free(cut->positions);
    if (cut->delim != NULL)
        free(cut->delim);
    return 0;
}

int my_getnbr(char *p)
{
    int i = 0;
    int c = 0;

    for (i = 0; p[i] != '\0'; i++) {
        if (p[i] <= '9' && p[i] >= '0')
            c = c * 10 + (p[i] - 48);
    }
    return c;
}

int my_strlen(char const *str)
{
    int i;

    if (str == NULL)
        return 0;
    i = 0;
    for (; str[i] != '\0'; i++);
    return i;
}

char *my_strdup(char *str)
{
    int i = 0;
    int lenght = my_strlen(str) + 1;
    char *new_string = malloc(lenght * sizeof(char));

    for (; str[i] != '\0'; i++)
        new_string[i] = str[i];
    new_string[i] = '\0';
    return new_string;
}
int count_char(char const *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            count++;
    }
    return count;
}

int count_sep(int i, char const *str, char sep)
{
    int count = 0;

    while (str[i] != sep && str[i] != '\0') {
        count++;
        i++;
    }
    return count;
}

char **my_str_to_word_array(char const *str, int nbre, char c)
{
    char **tab = NULL;
    int j = 0;
    int k = 0;

    tab = malloc((nbre + 2) * sizeof(char *));
    for (int i = 0; i <= nbre; i++) {
        k = 0;
        tab[i] = malloc(count_sep(j, str, c) + 1);
        for (; str[j] != c && str[j] != '\0'; j++) {
            tab[i][k] = str[j];
            k++;
        }
        tab[i][k] = '\0';
        j++;
    }
    tab[nbre + 1] = NULL;
    return tab;
}

char **word_array(char const *str, char c)
{
    int nombre_fois = count_char(str, c);
    char **tab = my_str_to_word_array(str, nombre_fois, c);

    return tab;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return s1[i] - s2[i];
}

cut_t *init_struct(cut_t *cut)
{
    cut = malloc(sizeof(cut_t));
    cut->c_activate = 0;
    cut->d_activate = 0;
    cut->f_activate = 0;
    cut->delim = my_strdup("\n");
    cut->positions = malloc(sizeof(char) * 10000);
    return cut;
}

cut_t *filling_struct(char **args, cut_t *cut)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "-c") == 0 || my_strcmp(args[i], "--characters") == 0) {
            cut->c_activate = 1;
            cut->positions = (args[i + 1] != NULL) ? my_strdup(args[i + 1]) : NULL;
        }
        if (my_strcmp(args[i], "-d") == 0 || my_strcmp(args[i], "--delimiter") == 0) {
            cut->d_activate = 1;
            cut->delim = (args[i + 1] != NULL) ? my_strdup(args[i + 1]) : NULL;
        }
        if (my_strcmp(args[i], "-f") == 0 || my_strcmp(args[i], "--fields") == 0) {
            cut->f_activate = 1;
            cut->positions = (args[i + 1] != NULL) ? my_strdup(args[i + 1]) : NULL;
        }
    }
    return cut;
}

int check_string(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
            return 84;
    }
    return 0;
}

int nb_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

int free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

int check_tab(char **tab)
{
    char **temp = NULL;

    for (int i = 0; tab[i] != NULL; i++) {
        temp = word_array(tab[i], '-');
        if (nb_tab(temp) == 0 || nb_tab(temp) > 2)
            return 84;
        free_tab(temp);
    }
    return 0;
}

int handle_error_cases(cut_t *cut)
{
    char **tab = NULL;

    if (cut->d_activate && (!cut->c_activate && !cut->f_activate))
        return 84;
    if (cut->c_activate && cut->f_activate)
        return 84;
    if (cut->delim == NULL || cut->positions == NULL)
        return 84;
    tab = word_array(cut->positions, ',');
    for (int i = 0; tab[i] != NULL; i++) {
        if (check_string(tab[i]))
            return 84;
    }
    if (check_tab(tab) == 84)
        return 84;
}

char *read_from_stdin(char *str)
{
    char temp[2];
    int nb = 0;
    int i = 0;

    temp[1] = '\0';
    nb = read(0, temp, 1);
    str[i] = temp[0];
    i++;
    while (nb > 0) {
        nb = read(0, temp, 1);
        str[i] = temp[0];
        i++;
    }
    str[i] = '\0';
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
    return str;
}

int char_in_string(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return 1;
    }
    return 0;
}

int update_deb_and_fin_values(char *str, int *deb, int *fin, char **tab, int k)
{
    char **tempo = NULL;

    if (!char_in_string(str, '-')) {
        *deb = my_getnbr(str) - 1;
        *fin = *deb;
    } else {
        if (str[0] == '-') {
            *deb = 0;
            *fin = my_getnbr(str) - 1;
        } else if (str[my_strlen(str) - 1] == '-') {
            *deb = my_getnbr(str) - 1;
            *fin = my_strlen(tab[k]) - 1;
        } else {
            tempo = word_array(str, '-');
            *deb = my_getnbr(tempo[0]) - 1;
            *fin = my_getnbr(tempo[1]) - 1;
        }
    }
    if (tempo != NULL)
        free_tab(tempo);
    return 0;
}

int display1(int deb, int fin, char **tab, int k, cut_t *cut)
{
    if (deb >= 0 && fin < nb_tab(tab) && k >= deb && k <= fin) {
        my_putstr(tab[k]);
        if (k + 1 < nb_tab(tab))
            write(1, &(cut->delim[0]), 1);
    }
    return 0;
}

int display2(int deb, int fin, char **tab, int k)
{
    for (int j = 0; tab[k][j] != '\0'; j++) {
        if (j >= deb && j <= fin && deb >= 0 && fin < my_strlen(tab[k]))
            write(1, &(tab[k][j]), 1);
    }
    return 0;
}

int display_string(char **tab, cut_t *cut, int k)
{
    char **temp = word_array(cut->positions, ',');
    int deb = 0;
    int fin = 0;


    for (int i = 0; temp[i] != NULL; i++) {
        update_deb_and_fin_values(temp[i], &deb, &fin, tab, k);
        if (cut->f_activate)
            display1(deb, fin, tab, k, cut);
        else
            display2(deb, fin, tab, k);
    }
    free_tab(temp);
    return 0;
}

int case1(char **tab, char *str, char **cutt, cut_t *cut)
{
    tab = word_array(str, '\n');
    for (int i = 0; tab[i] != NULL; i++) {
        cutt = word_array(tab[i], cut->delim[0]);
            for (int j = 0; cutt[j] != NULL; j++)
                display_string(cutt, cut, j);
            free_tab(cutt);
            if (tab[i + 1] != NULL)
                write(1, "\n", 1);
    }
    free_tab(tab);
    return 0;
}

int case2(char **tab, char *str, cut_t *cut)
{
    tab = word_array(str, cut->delim[0]);
    for (int i = 0; tab[i] != NULL; i++) {
        display_string(tab, cut, i);
        if (tab[i + 1] != NULL)
            write(1, "\n", 1);
    }
    free_tab(tab);
    return 0;
}

int execute_all(char *str, cut_t *cut)
{
    char **tab = NULL;
    char **cutt = NULL;

    if (my_strcmp(cut->delim, "\n") != 0)
        case1(tab, str, cutt, cut);
    else
        case2(tab, str, cut);
    free(str);
    return 0;
}

int main(int argc, char **argv)
{
    char *str = malloc(sizeof(char) * SIZE);
    cut_t *struc = NULL;

    str = read_from_stdin(str);
    struc = init_struct(struc);
    struc = filling_struct(argv, struc);
    if (handle_error_cases(struc) == 84) {
        free_struct(struc);
        return 84;
    }
    execute_all(str, struc);
    free_struct(struc);
    return 0;
}