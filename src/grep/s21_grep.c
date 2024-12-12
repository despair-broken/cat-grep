#include "s21_grep.h"

int main(int argc, char **argv) {
  arguments arg = arguments_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}

arguments arguments_parser(int argc, char *argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_words_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.len_pat == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void pattern_add(arguments *arg, char *pattern) {
  if (arg->len_pat != 0) {
    strcat(arg->pattern + arg->len_pat, "|");
    arg->len_pat++;
  }
  arg->len_pat += sprintf(arg->pattern + arg->len_pat, "(%s)", pattern);
}

void add_words_from_file(arguments *arg, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) {
      perror(filepath);
    }
  } else {
    char *line = NULL;
    size_t memlen = 0;
    int read = getline(&line, &memlen, f);
    while (read != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern_add(arg, line);
      read = getline(&line, &memlen, f);
    }
    free(line);
    fclose(f);
  }
}

void output(arguments arg, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    perror("Error compiling regex");
  } else {
    for (int i = optind; i < argc; i++) {
      processfile(arg, argv[i], &re);
    }
    regfree(&re);
  };
}

void processfile(arguments arg, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    return;
  }
  char *line = NULL;
  size_t memlen = 0;
  int read;
  int line_counter = 1;
  int count = 0;
  while ((read = getline(&line, &memlen, f)) != -1) {
    int word = regexec(reg, line, 0, NULL, 0);
    if ((word == 0 && !arg.v) || (arg.v && word != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_counter);
        if (arg.o) {
          print_mat(reg, line);
        } else {
          output_line(line, read);
        }
      }
      count++;
    }
    line_counter++;
  }
  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", count);
  }
  if (arg.l && count > 0) printf("%s\n", path);
  fclose(f);
}

void print_mat(regex_t *re, char *line) {
  regmatch_t match;
  int off = 0;
  int res;

  while ((res = regexec(re, line + off, 1, &match, 0)) == 0) {
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    off += match.rm_eo;
  }
  if (res != 0) {
    fprintf(stderr, "Error executing regex: %d\n", res);
  }
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}