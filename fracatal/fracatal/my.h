/*
** EPITECH PROJECT, 2023
** fracatal
** File description:
** my.h
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef MY_H
    #define MY_H
char **str_to_array(char *str, char *sep);
int count(char *str, char c);
char **remp(char **fract, char **arr, int *l, int *c);
char **fractal(char *str, char **arr1, char **arr2);
int free_array(char **arr);
int count_dot_diez(char *str);
int nb_str_in_array(char **arr);
#endif
