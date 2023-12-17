#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

typedef struct {
    int b, e, E, v, n, s, t, T;
} arguments;

arguments *parser(int argc, char** argv) {
    arguments arg = {0};
    int flag = 0;
    const struct option long_options[] = {
            {"number-nonblank", no_argument, NULL, 'b'},
            {"number",          no_argument, NULL, 'n'},
            {"squeeze-blank",   no_argument, NULL, 's'},
            {NULL, 0,                        NULL, 0}
    };
    while (flag != -1) {
        flag = getopt_long(argc, argv, "benstET", long_options, NULL);
        switch (flag) {
            case 'b':
                arg.b = 1;
                printf("b %d \n", flag);
                break;
            case 'e':
                arg.e = 1;
                arg.v = 1;
                printf("e %d \n", flag);
                break;
            case 'n':
                arg.n = 1;
                printf("n %d \n", flag);
                break;
            case 's':
                arg.s = 1;
                printf("s %d \n", flag);
                break;
            case 't':
                arg.t = 1;
                arg.v = 1;
                printf("t %d \n", flag);
                break;
            case 'E':
                arg.e = 1;
                break;
            case 'T':
                arg.t = 1;
                break;
            default:
                break;
        }
    }
}

int main(int argc, char** argv) {
    FILE *f = fopen(argv[argc - 1], "r");
    if (f == NULL) {
        perror("Ошибка при открытии файла");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, f);

    while (read != -1) {
        printf("%s", line);
    }

    free(line);
    fclose(f);

    return EXIT_SUCCESS;
}