/*
** EPITECH PROJECT, 2024
** mliuyt
** File description:
** kjhgfd
*/

#include "my.h"

int error_case(int argc, char **argv)
{
    if (strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "-s") != 0)
        exit(84);
    if (strlen(argv[2]) == 0)
        exit(84);
    for (int a = 0; argv[3][a] != '\0'; a++) {
        if (argv[3][a] >= '0' && argv[3][a] <= '9')
            continue;
        if (argv[3][a] == '-')
            continue;
        exit(84);
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 84;
    error_case(argc, argv);
    if (strcmp(argv[1], "-f") == 0)
        flag_file(argv[2], atoi(argv[3]));
    if (strcmp(argv[1], "-s") == 0)
        flag_string(argv[2], atoi(argv[3]));
}
