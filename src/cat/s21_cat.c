#include "s21_cat.h"

int main(int argc, char *argv[]) {
  base_flags my_flags = parser(argc, argv);
  printer(my_flags, argc, argv);
  return 0;
}

base_flags parser(int argc, char **argv) {
  base_flags my_flags = {0};
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
  int ret;
  while ((ret = getopt_long(argc, argv, "snbveEtT", long_options, 0)) != -1) {
    switch (ret) {
      case 's':
        my_flags.s = 1;
        break;
      case 'n':
        my_flags.n = 1;
        break;
      case 'b':
        my_flags.b = 1;
        break;
      case 'v':
        my_flags.v = 1;
        break;
      case 'e':
        my_flags.e = 1;
        break;
      case 'E':
        my_flags.E = 1;
        break;
      case 't':
        my_flags.t = 1;
        break;
      case 'T':
        my_flags.T = 1;
        break;
      default:
        break;
    }
  }
  process_struct(&my_flags);
  return my_flags;
}

void process_struct(base_flags *base_flags) {
  if (base_flags->b) {
    base_flags->n = 0;
  }
  if (base_flags->e) {
    base_flags->E = 1;
    base_flags->v = 1;
    base_flags->e = 0;
  }
  if (base_flags->t) {
    base_flags->T = 1;
    base_flags->v = 1;
    base_flags->t = 0;
  }
}

void printer(base_flags my_flags, int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      FILE *f = fopen(argv[i], "r");
      if (f != NULL) {
        reader(my_flags, f);
      }
      fclose(f);
    }
  }
}

void reader(base_flags my_flags, FILE *f) {
  int pre_che = '\n';
  int ch = 0;
  int empty_ch = 1;
  int line_count = 1;
  while ((ch = fgetc(f)) != EOF) {
    if (my_flags.s) {
      flag_s(ch, &empty_ch);
    }
    if (my_flags.n) {
      flag_n(pre_che, &empty_ch, &line_count);
    }
    if (my_flags.b) {
      flag_b(pre_che, ch, &line_count);
    }
    if (my_flags.v) {
      ch = flag_v(ch);
    }
    if (my_flags.E) {
      flag_E(ch, pre_che, &empty_ch, my_flags.b);
    }
    if (my_flags.T) {
      ch = flag_T(ch);
    }

    if (empty_ch < 3) {
      putchar(ch);
    }
    pre_che = ch;
  }
}

void flag_s(int ch, int *empty_ch) {
  if (ch == '\n') {
    (*empty_ch)++;
  } else {
    (*empty_ch) = 0;
  }
}

void flag_n(int pre_che, int *empty_ch, int *line_count) {
  if ((pre_che == '\n') && (*empty_ch < 3)) {
    printf("%6d\t", *line_count);
    (*line_count)++;
  }
}

void flag_b(int pre_che, int ch, int *line_count) {
  if ((pre_che == '\n') && (ch != '\n')) {
    printf("%6d\t", *line_count);
    (*line_count)++;
  }
}

int flag_v(int ch) {
  if (ch < 32 && ch != 9 && ch != 10) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = 63;
  }
  return ch;
}

void flag_E(int ch, int pre_che, int *empty_ch, int b) {
  if ((ch == '\n') && (pre_che == '\n') && (b) && (*empty_ch < 3)) {
    printf("      \t");
  }
  if ((ch == '\n') && (*empty_ch < 3)) {
    printf("$");
  }
}

int flag_T(int ch) {
  if (ch == '\t') {
    printf("^");
    ch = 'I';
  }
  return ch;
}