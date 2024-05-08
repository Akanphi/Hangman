/*
** EPITECH PROJECT, 2024
** kznd
** File description:
** zdisqn
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

typedef struct game {
    int nb_chances;
    char *mot;
} game_t;

char *open_file(char *filepath)
{
    struct stat info;
    char *str = NULL;
    int size = 0;
    int fd = 0;
    int r = 0;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return NULL;
    stat(filepath, &info);
    size = info.st_size;
    if (size == 0)
        return NULL;
    str = malloc(sizeof(char) * (size + 1));
    r = read(fd, str, size);
    str[size - 1] = '\0';
    close(fd);
    return str;
}

int count_char(char const *str, char c)
{
    int count = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

int nb_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

int count_sep(int i, char const *str, char sep)
{
    int count = 0;

    while (str[i] != sep && str[i] != '\0') {
        count++;
        i++;
    }
    return count;
}

char **my_str_to_word_array(char const *str, int nbre, char c)
{
    char **tab = NULL;
    int j = 0;
    int k = 0;

    tab = malloc((nbre + 2) * sizeof(char *));
    for (int i = 0; i <= nbre; i++) {
        k = 0;
        tab[i] = malloc(count_sep(j, str, c) + 1);
        for (; str[j] != c && str[j] != '\0'; j++) {
            tab[i][k] = str[j];
            k++;
        }
        tab[i][k] = '\0';
        j++;
    }
    tab[nbre + 1] = NULL;
    return tab;
}

char **word_array(char const *str, char c)
{
    int nombre_fois = count_char(str, c);
    char **tab = my_str_to_word_array(str, nombre_fois, c);

    return tab;
}

int bad_character(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 1;
    }
    return 0;
}

char *read_from_stdin(void)
{
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read = getline(&input, &buffer_size, stdin);

    input[strlen(input) - 1] = '\0';
    return input;
}

int error_cases(int argc, char **argv)
{
    char *str = NULL;

    if (argc != 2)
        return 84;
    str = open_file(argv[1]);
    if (str == NULL)
        return 84;
    if (strlen(str) == 0)
        return 84;
}

int choose_random(char **tab)
{
    srand(time(NULL));
    return rand() % (nb_tab(tab));
}

game_t *init_struct(game_t *game, int argc, char **argv)
{
    char *str = open_file(argv[1]);
    char **tab = word_array(str, '\n');
    int index = choose_random(tab);

    game->mot = tab[index];
    game->nb_chances = strlen(game->mot);
    return game;
}

int first_displaying(game_t *game)
{
    printf("*: invalid letter\n");
    printf("?: incorrectly placed letter\n");
    printf("Will you find the secret word?\n");
    printf("%c", game->mot[0]);
    for (int i = 1; i < strlen(game->mot); i++)
        printf("*");
    printf("\n\n");
    return 0;
}

int displaying(char *str, char *mot, game_t *game)
{
    int r = 0;
    int seen[1000] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == game->mot[i]) {
            printf("%c", str[i]);
            seen[i] = 1;
        } else if (strchr(game->mot, str[i]) && !seen[strchr(mot, str[i]) - mot])
            printf("?");
        else
            printf("*");
    }
    printf("\n\n");
    return 0;
}

char *check(char *str, game_t *game)
{
    while (strlen(str) != strlen(game->mot)) {
        if (strlen(str) < strlen(game->mot))
            printf("Word too short. Retry.\n");
        else
            printf("Word too long. Retry.\n");
        printf(">");
        str = read_from_stdin();
    }
    return str;
}

int game_play(game_t *game)
{
    char *str = NULL;
    int round = 1;

    first_displaying(game);
    while (1) {
        printf("Round %d\n", round);
        printf(">");
        round += 1;
        str = read_from_stdin();
        str = check(str, game);
        displaying(str, game->mot, game);
        if (strcmp(str, game->mot) == 0)
            break;
        game->nb_chances --;
        if (game->nb_chances == 0)
            break;
    }
    if (game->nb_chances == 0)
        printf("You lost!\n");
    else
        printf("You won!\n");
    return 0;
}

int main(int argc, char **argv)
{
    game_t *game = malloc(sizeof(game_t));

    if (error_cases(argc, argv) == 84)
        return 84;
    game = init_struct(game, argc, argv);
    return game_play(game);
}
