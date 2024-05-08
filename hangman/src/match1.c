#include "../include/my.h"
#include <time.h>

char *replace(char *modevin, char *motactu, char c)
{
    for (int i = 0; modevin[i] != '\0'; i++) {
        if (modevin[i] == c)
            motactu[i] = c;
    }
    return motactu;
}

char *remochar(char *modevin, char *motactu, char c)
{
    for (int i = 0; modevin[i] != '\0'; i++) {
        if (modevin[i] == c)
            modevin[i] = '*';
    }
    return modevin;
}

void hangman(char **dico, int essay)
{
    int len = 0;
    char *modevin = NULL;
    char *motactu = NULL;
    char chara = '\0';
    char *ptr = NULL;
    int index = 0;

    for (; dico[len] != NULL; len++);
    srand(time(NULL));
    int num = rand() % len;
    modevin = strdup(dico[num]);
    motactu = malloc((strlen(modevin) + 1) * sizeof(char));
    memset(motactu, '*', strlen(modevin));
    motactu[strlen(modevin)] = '\0';

    while (1) {
        printf("%s\n", motactu);
        printf("Tries: %d\n\n", essay);
        printf("Your letter: ");
        scanf(" %c", &chara);
        ptr = strchr(modevin, chara);
        if (ptr != NULL) {
            index = ptr - modevin;
            replace(modevin, motactu, chara);
            remochar(modevin, motactu, chara);
        } else {
            printf("%c: is not in this word\n", chara);
            essay--;
        }
        if (essay == 0) {
            printf("Tries: %d\n\n", essay);
            break;
        }
        if (!strchr(motactu, '*'))
            break;
    }
    if (essay == 0 && strchr(motactu, '*')) {
        printf("You lost!\n");
    } else {
        printf("%s\n", motactu);
        printf("\nCongratulations!\n");
    }
    free(modevin);
    free(motactu);
}