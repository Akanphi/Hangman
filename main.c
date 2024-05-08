#include "../include/my.h"

void freedoub(char **str)
{
    for (int i = 0; str[i] != NULL; i++) {
        free(str[i]);
    }
    free(str);
}

int main(int argc, char **argv)
{
    int essay = 0;
    char *file = NULL;
    char **dico = NULL;

    verror(argc, argv);
    if (argc == 3) {
        essay = atoi(argv[2]);
    }
    file = load_file_in_mem(argv[1]);
    if (strlen(file) < 2)
        exit(84);
    for (int i = 0; file[i] != '\0'; i++) {
        if (file[i] != '\n' && !isalpha(file[i]))
            exit(84);
    }
    if (essay == 0)
        essay = 10;
    dico = my_strtok(file);
    free(file);
    hangman(dico, essay);
    freedoub(dico);
    return 0;
}