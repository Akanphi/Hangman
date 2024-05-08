/*
** EPITECH PROJECT, 2024
** game.h
** File description:
** header of our program
*/

#ifndef GAME_H
    #define GAME_H
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>

int verror(int argc, char **argv);
char *load_file_in_mem(char *filepath);
char **my_strtok(char *file);
void hangman(char **dico, int essay);
#endif
