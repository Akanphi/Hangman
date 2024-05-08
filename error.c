#include "../include/my.h"

int verror(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
        exit(84);
    if (argc == 3) {
        for (int i = 0; argv[2][i] != '\0'; i++) {
            if (!isdigit(argv[2][i]))
                exit(84);
        }
    }
    return 0;
}

int fs_open_file(char *filepath)
{
    int fd = 0;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        exit(84);
    return fd;
}

int file_size(char *filepath)
{
    struct stat info;
    off_t size;

    stat(filepath, &info);
    size = info.st_size;
    return size;
}

char *load_file_in_mem(char *filepath)
{
    int x = file_size(filepath);
    char *buffer = malloc((x + 1) * sizeof(char));
    int fd = fs_open_file(filepath);
    int reader = read(fd, buffer, x);

    buffer[reader] = '\0';
    close(fd);
    return buffer;
}