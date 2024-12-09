#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pat;
} arguments;

arguments arguments_parser(int argc, char *argv[]);
void pattern_add(arguments *arg, char *pattern);
void add_words_from_file(arguments *arg, char *filepath);
void output(arguments arg, int argc, char **argv);
void processfile(arguments arg, char *path, regex_t *reg);
void print_mat(regex_t *re, char *line);
void output_line(char *line, int n);