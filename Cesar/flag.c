/*
** EPITECH PROJECT, 2024
** koihugytfr
** File description:
** knbjhgcfd
*/

#include "my.h"

int flag_string(char *str, int key)
{
    int fd = open("crypt", O_RDWR | O_CREAT | O_TRUNC,
    S_IRUSR | S_IRGRP | S_IROTH);
    char *src = cesar(str, key);

    write(fd, src, strlen(src));
    close(fd);
    free(src);
    return 0;
}

int flag_file(char *str, int key)
{
    char *s = load_file_in_mem(str);
    char *src = cesar(s, key);
    int fd = open("crypt", O_RDWR | O_CREAT | O_TRUNC,
    S_IRUSR | S_IRGRP | S_IROTH);

    write(fd, src, strlen(src));
    close(fd);
    free(src);
    free(s);
    return 0;
}
