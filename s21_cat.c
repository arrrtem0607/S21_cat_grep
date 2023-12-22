#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int b, e, E, v, n, s, t, T;
} arguments;

void parser(int argc, char** argv, arguments* arg);
void openfile(int argc, char ** argv, arguments* arg);
void catnoflag(FILE* f);
void cat_e(FILE* f);
void cat_t(FILE* f);

int main(int argc, char** argv) {
    arguments arg = {0};
    parser(argc, argv, &arg);
    openfile(argc, argv, &arg);
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
        flag = getopt_long(argc, argv, "+benstET", long_options, NULL);
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

void catnoflag(FILE* f){
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        fputc(ch, stdout);
    }
}

void cat_e(FILE* f){
    int ch;
    while((ch = fgetc(f)) != EOF){
        if (ch == '\n'){
            fputc('$', stdout);
        }
        fputc(ch, stdout);
    }
}

void cat_t(FILE* f){
    int ch;
    while((ch = fgetc(f)) != EOF){
        if (ch == '\t'){
            fputc('^', stdout);
            fputc('I', stdout);
            continue;
        }
        fputc(ch, stdout);
    }
}

void cat_n(FILE* f){
    int ch_pred;
    int ch;
    int count = 1;
    printf("%6d  ", count);
    while((ch = fgetc(f)) != EOF){
        if (ch_pred == '\n') {
            count++;
            printf("%6d  ", count);
            fputc(ch, stdout);
            ch_pred = ch;
        } else {
            fputc(ch, stdout);
            ch_pred = ch;
        }
    }
}

void cat_s(FILE* f){
    int ch;
    while((ch = fgetc(f)) != EOF){
        if (ch == '\n') {
            continue;
        }
        fputc(ch, stdout);
    }
}


void openfile(int argc, char ** argv, arguments* arg){
    for (int i = optind; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL) {
            printf("%s: %s: No such file or directory\n", argv[0], argv[i]);
            exit(1);
        }
        if (arg -> e) {
            cat_e(f);
        }
        if (arg -> t) {
            cat_t(f);
        }
        if (arg -> n) {
            cat_n(f);
        }
        if (arg -> s) {
            cat_s(f);
        }
        if (!arg ->b && !arg -> e && !arg -> v && !arg -> n && !arg -> s && !arg -> t){
            catnoflag(f);
        }
    }
}
