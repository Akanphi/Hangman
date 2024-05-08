/*
** EPITECH PROJECT, 2023
** B-CPE-200-COT-2-1-bsrobotfactory-jordan.amouzoun
** File description:
** file.h
*/

#include "my.h"

char *load_file_in_mem(char const *filepath)
{
    int fd;
    struct stat inf;
    char *s;
    int long size;

    stat(filepath, &inf);
    s = malloc((inf.st_size + 1) * sizeof(char));
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        exit(84);
    size = read(fd, s, inf.st_size);
    s[size] = '\0';
    close(fd);
    return s;
}
