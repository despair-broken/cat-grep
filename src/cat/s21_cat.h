#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct base_flags {
  int s, n, b, v, e, E, t, T;
} base_flags;

base_flags parser(int argc, char **argv);
void process_struct(base_flags *base_flags);
void printer(base_flags my_flags, int argc, char *argv[]);
void reader(base_flags my_flags, FILE *f);

void flag_s(int ch, int *empty_ch);
void flag_n(int pre_che, int *empty_ch, int *line_count);
void flag_b(int pre_che, int ch, int *line_count);
int flag_v(int ch);
void flag_E(int pre_che, int ch, int *empty_ch, int b);
int flag_T(int ch);
