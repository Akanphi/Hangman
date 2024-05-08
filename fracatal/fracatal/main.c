/*
** EPITECH PROJECT, 2023
** fracatal
** File description:
** main.c
*/

#include "my.h"

int free_array(char **arr)
{
    int a = 0;

    for (a = 0; arr[a] != NULL; a++)
        free(arr[a]);
    free(arr[a]);
    free(arr);
}

int main(int argc, char **argv)
{
    char **arr1 = str_to_array(argv[2], "@");
    char **arr2 = str_to_array(argv[3], "@");

    for (int a = 1; a < atoi(argv[1]); a++) {
        arr1 = fractal(argv[2], arr1, arr2);
        arr2 = fractal(argv[3], arr1, arr2);
    }
    for (int a = 0; arr1[a] != NULL; a++)
        printf("%s\n", arr1[a]);
    free_array(arr1);
    free_array(arr2);
}
