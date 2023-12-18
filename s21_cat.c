#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int b, e, E, v, n, s, t, T;
} arguments;

void parser(int argc, char** argv, arguments* arg);
void output(int argc, char** argv);
void output_n(int argc, char** argv);

int main(int argc, char** argv) {
    arguments arg = {0};
    parser(argc, argv, &arg);
    /*if (arg -> n == 1) {
        output_n(argc, argv);
    } else {
        output(argc, argv);
    }*/
    printf("\nb:%d e:%d v:%d n:%d s:%d t:%d", arg.b, arg.e, arg.v, arg.n, arg.s, arg.t);
    return 0;
}

void parser(int argc, char** argv, arguments* arg) {
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
                arg -> b = 1;
                break;
            case 'e':
                arg -> e = 1;
                arg -> v = 1;
                break;
            case 'n':
                arg -> n = 1;
                break;
            case 's':
                arg -> s = 1;
                break;
            case 't':
                arg -> t = 1;
                arg -> v = 1;
                break;
            case 'E':
                arg -> e = 1;
                break;
            case 'T':
                arg -> t = 1;
                break;
            default:
                break;
        }
    }
}

void output(int argc, char** argv){
    for (int i = optind; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        char *toprint = NULL;
        size_t memtoprint = 0;
        ssize_t read;
        while ((read = getline(&toprint, &memtoprint, f)) != -1) {
            printf("%s", toprint);
        }
        free(toprint);
        fclose(f);
    }
}

void output_n(int argc, char** argv){
    for (int i = optind; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        char *toprint = NULL;
        size_t memtoprint = 0;
        ssize_t read;
        int stroka = 1;
        while ((read = getline(&toprint, &memtoprint, f)) != -1) {
            printf("%d %s", stroka, toprint);
            stroka++;
        }
        free(toprint);
        fclose(f);
    }
}