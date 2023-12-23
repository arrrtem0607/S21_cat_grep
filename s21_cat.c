#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int b, e, E, v, n, s, t, T;
} arguments;

void parser(int argc, char** argv, arguments* arg);
void openfile(int argc, char ** argv, arguments* arg);

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

void catnoflag(int * c){
    fputc(*c, stdout);
}

void cat_e(int * ch, arguments* a) {
    fputc('$', stdout);
    if ((*ch == '\n' || *ch == '\t') && a -> n){
    } else if ((*ch <= 31) && a -> n){
        fputc('^', stdout);
        *ch += 64;
    } else if ((*ch == 127) && a -> n){
        fputc('^', stdout);
        *ch = '?';
    }
}


void cat_t(int * ch, arguments* a){
    if (*ch == '\t'){
        fputc('^', stdout);
        fputc('I', stdout);
    }
    if ((*ch == '\n' || *ch == '\t') && a -> n){
    } else if ((*ch <= 31) && a -> n){
        fputc('^', stdout);
        *ch += 64;
    } else if ((*ch == 127) && a -> n){
        fputc('^', stdout);
        *ch = '?';
    }
    //fputc(*c, stdout);
}

void cat_n (int * nachalo, int * ch_pred, int * count){
    if (*nachalo){
        printf("%6d  ", *count);
        *nachalo = 0;
    }
    if (*ch_pred == '\n') {
        *count += 1;
        printf("%6d  ", *count);
        //fputc(*c, stdout);
    } else {
        //fputc(*c, stdout);
    }
}

void cat_s(int * ch, int * ch_pred, int * s) {
    if (*s == 0 && *ch != '\n') {
        *s = 1;
    }
    if (*s) {
        if (*ch == '\n' && *ch_pred == '\n') {
            //fputc(*ch, stdout);
            *s = 0;
        } else {
            //fputc(*ch, stdout);
        }
    }
}

void cat_b(int * ch, int * nachalo, int* ch_pred, int* count) {
    if (*nachalo){
        printf("%6d  ", *count);
        *nachalo = 0;
    }
    if (*ch == '\n' && *ch_pred != '\n') {
        *count += 1;
        //fputc(*ch, stdout);
    } else if (*ch == '\n' && *ch_pred == '\n') {
        //fputc(*ch, stdout);
    } else if (*ch != '\n' && *ch_pred == '\n') {
        printf("%6d  ", *count);
        //fputc(*ch, stdout);
    } else {
        //fputc(*ch, stdout);
    }
}

/*void cat_v(int * ch){
    if (*ch == '\n' || *ch == '\t'){
    }
    if (*ch <= 31){
        fputc('^', stdout);
        fputc(*ch + 64, stdout);
    } else if (*ch == 127){
        fputc('^', stdout);
        fputc('?', stdout);
    }
}*/


void openfile(int argc, char ** argv, arguments* arg){
    for (int i = optind; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL) {
            printf("%s: %s: No such file or directory\n", argv[0], argv[i]);
            exit(1);
        }
        int ch;
        int count = 1;
        int nachalo = 1;
        int ch_pred;
        int s = 1;
        while ((ch = fgetc(f)) != EOF) {
            if (ch == '\n'){
                if (arg -> e) {
                    fputc('$', stdout);
                }
            } else if (ch == '\t'){
                if (arg -> t) {
                    fputc('^', stdout);
                    fputc('I', stdout);
                }
            }
            fputc(ch, stdout);
        }
    }
}
