/*
** EPITECH PROJECT, 2024
** ndq
** File description:
** sdqs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    int nbre;
    struct node *next;
    struct node *previous;
} node_t;

typedef struct linked_list {
    node_t *begin;
    node_t *end;
    int lenght;
} linked_list_t;

typedef struct verif {
    char *s1;
    char *s2;
    int sort;
    int groupby;
} ver_t;

linked_list_t *create_list(linked_list_t *list)
{
    list = malloc(sizeof(linked_list_t));
    list->begin = NULL;
    list->end = NULL;
    list->lenght = 0;
    return list;
}

int is_empty_list(linked_list_t *list)
{
    if (list->begin == NULL && list->end == NULL
        && list->lenght == 0)
        return 1;
    return 0;
}

node_t *create_node(char ch, int nb)
{
    node_t *node = malloc(sizeof(node_t));

    node->c = ch;
    node->nbre = nb;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

linked_list_t *add_back(node_t *node, linked_list_t *list)
{
    if (is_empty_list(list)) {
        list->begin = node;
        list->end = node;
        list->lenght += 1;
        return list;
    }
    list->end->next = node;
    node->previous = list->end;
    list->end = list->end->next;
    list->lenght += 1;
    return list;
}

linked_list_t *at_beginning(node_t *a, linked_list_t *list)
{
    a->previous = NULL;
    a->next = list->begin;
    list->begin->previous = a;
    list->begin = a;
    list->lenght += 1;
    return list;   
}

linked_list_t *at_end(node_t *a, linked_list_t *list)
{
    list->end->next = a;
    a->previous = list->end;
    a->next = NULL;
    list->end = a;
    list->lenght += 1;
    return list;
}

linked_list_t *insert_right_position(node_t *a, linked_list_t *list)
{
    node_t *node = NULL;
    node_t *temp = create_node(a->c, a->nbre);

    if (temp->nbre >= list->begin->nbre)
        return at_beginning(temp, list);
    if (temp->nbre <= list->end->nbre)
        return at_end(temp, list);
    node = list->begin->next;
    while (node->next != NULL && node->nbre > temp->nbre)
        node = node->next;
    temp->previous = node->previous;
    temp->next = node;
    node->previous->next = temp;
    node->previous = temp;
    list->lenght += 1;
    return list;
}

linked_list_t *insertion_sort(linked_list_t *list)
{
    linked_list_t *new = create_list(new);
    node_t *temp = NULL;

    if (is_empty_list(list) || list->lenght == 1)
        return list;
    temp = create_node(list->begin->c, list->begin->nbre);
    new = add_back(temp, new);
    for (node_t *a = list->begin->next; a != NULL; a = a->next)
        new = insert_right_position(a, new);
    return new;
}

int count_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            count++;
    }
    return count;
}

int char_in_str(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return 1;
    }
    return 0;
}

int disp_list(linked_list_t *list)
{
    node_t *actuel = list->begin;

    while (actuel != NULL)
    {
        printf("%c:%d\n", actuel->c, actuel->nbre);
        actuel = actuel->next;
    }
    return 0;
}

int my_strlen(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        count += 1;
    return count;
}

int error_cases(int argc, char **argv)
{
    if (argc > 5)
        return 84;
    for (int i = 1; i < argc; i++) {
        if (my_strlen(argv[i]) == 2 && argv[i][0] == '-'
        && argv[i][1] != 'r' && argv[i][1] != 't')
            return 84;
    }
    return 0;
}

linked_list_t *duplicate_list(linked_list_t *list)
{
    linked_list_t *new = create_list(new);
    node_t *node = list->begin;

    while (node != NULL) {
        new = add_back(node, new);
        node = node->next;
    }
    return new;
}

char *to_char(char c)
{
    char *new = malloc(sizeof(char) * 2);

    new[0] = c;
    new[1] = '\0';
    return new;
}

char *my_strcat(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int total_len = len1 + len2;
    char *result = malloc(sizeof(char) * (total_len + 1));

    strcpy(result, s1);
    strcat(result, s2);   
    return result;
}

int decoup(linked_list_t *others, node_t *node, int *seen)
{
    char *str = "\0";
    char *temp = NULL;
    node_t *actuel = others->begin;

    while (actuel != NULL) {
        if (node->nbre == actuel->nbre) {
            temp = my_strcat(to_char(actuel->c), ",");
            str = my_strcat(str, temp);
        }
        actuel = actuel->next;
    }
    if (str[my_strlen(str) - 1] == ',')
        str[my_strlen(str) - 1] = ':';
    printf("%s%d\n", str, node->nbre);
    seen[node->nbre] = 1;
}

int display_list(linked_list_t *list)
{
    node_t *node = list->begin;
    linked_list_t *others = duplicate_list(list);
    int seen[1000] = {0};


    while (node != NULL) {
        if (seen[node->nbre] == 1) {
            node = node->next;
            continue;
        }
        decoup(others, node, seen);
        node = node->next;
    }
    return 0;
}

int help_occurences(ver_t *s, int *seen, node_t *node, linked_list_t *liste)
{
    for (int i = 0; s->s1[i] != '\0'; i++) {
        if (seen[s->s1[i]] == 0 && char_in_str(s->s2, s->s1[i])) {
            node = create_node(s->s1[i], count_char(s->s1, s->s1[i]));
            liste = add_back(node, liste);
            seen[s->s1[i]] = 1;
        }
    }
    for (int i = 0; s->s2[i] != '\0'; i++) {
        if (!char_in_str(s->s1, s->s2[i])) {
            node = create_node(s->s2[i], 0);
            liste = add_back(node, liste);  
        }
    }
    return 0;
}

int nbre_occurences(ver_t *s)
{
    int seen[1000] = {0};
    node_t *node = NULL;
    linked_list_t *liste = create_list(liste);

    help_occurences(s, seen, node, liste);
    if (s->sort)
        liste = insertion_sort(liste);
    if (s->groupby)
        display_list(liste);
    else
        disp_list(liste);
    return 0;
}

int fill_struct(char **argv, int i, ver_t *s, int *turn)
{
    if (strcmp(argv[i], "-r") == 0)
        s->groupby = 1;
    else if (strcmp(argv[i], "-t") == 0)
        s->sort = 1;
    else {
        if (*turn % 2 == 0)
            s->s1 = strdup(argv[i]);
        else
            s->s2 = strdup(argv[i]);
        (*turn) += 1;
    }
    return 0;
}

ver_t *init_struct(ver_t *s, int argc, char **argv)
{
    int turn = 0;

    s->groupby = 0;
    s->sort = 0;
    s->s1 = NULL;
    s->s2 = NULL;
    for (int i = 1; i < argc; i++)
        fill_struct(argv, i, s, &turn);
    if (s->s2 == NULL)
        s->s2 = strdup(s->s1);
    return s;
}

int main(int argc, char **argv)
{
    ver_t *stru = malloc(sizeof(ver_t));

    if (error_cases(argc, argv) == 84)
        return 84;
    stru = init_struct(stru, argc, argv);
    return nbre_occurences(stru);
}
