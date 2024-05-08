/*
** EPITECH PROJECT, 2023
** B-CPE-210-COT-2-1-stumper2-michael.gbekan
** File description:
** my
*/
#ifndef MY_H_
    #define MY_H_
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <criterion/criterion.h>
    #include <criterion/redirect.h>
char verif_alph(char c, int key, char a, char z);
char *cesar(char *str, int key);
char *load_file_in_mem(char const *filepath);
int flag_string(char *str, int key);
int flag_file(char *str, int key);
#endif
