#include "../include/my.h"

char **my_strtok(char *file)
{
    char *token = NULL;
    int len  = strlen(file);
    char **mots = malloc((len + 1) * sizeof(char *));
    int i = 0;

    token = strtok(file, "\n");
    while (token != NULL && !strchr(token, '\n')) {
        mots[i] = strdup(token);
        i++;
        token = strtok(NULL, "\n");
    }
    mots[i] = NULL;
    return mots;
}