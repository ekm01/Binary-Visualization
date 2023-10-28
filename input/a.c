#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TokenList {
  char **list;
  unsigned int len_par; // number of tokens with parentheses
  unsigned int len;     // without parentheses
} TokenList;

TokenList tokenize(char *program, unsigned int length) {
  // length must be half of the program length according to worst case due to
  // pretokenize()

  // strtok() to tokenize the items separated by space
  const char *delim = " ";

  unsigned int y = 0;
  unsigned int partrack = 0;

  char *token = strtok(program, delim);

  if (strcmp(token, ")") == 0) {
    fprintf(stderr, "Syntax Error occured!\n");
    exit(1);
  }

  TokenList tokenlist;
  tokenlist.list = (char **)malloc(length * sizeof(char *));

  if (tokenlist.list == NULL) {
    fprintf(stderr, "Memory cannot be allocated!\n");
    exit(1);
  }

  // further tokenization and creating token list
  unsigned int i = 0;
  while (token != NULL) {
    tokenlist.list[i] = token;

    if (strcmp(token, "(") == 0) {
      y++;
      partrack++;
    } else if (strcmp(token, ")") == 0) {
      y++;
      partrack--;
    }

    if (partrack < 0) {
      fprintf(stderr, "Syntax Error occured!\n");
      exit(1);
    }

    token = strtok(NULL, delim);
    i++;
  }

  if (partrack != 0) {
    fprintf(stderr, "Syntax Error occured!\n");
    exit(1);
  }

  tokenlist.len_par = i;
  tokenlist.len = i - y;
  return tokenlist;
}

int main(int argc, char *argv[]) {
  char s[] = "( + 32 5 )";
  size_t l = strlen(s);
  char *anan = malloc(l * sizeof(char));
  strncpy(anan, s, l + 1);
  printf("%s\n", anan);
  return EXIT_SUCCESS;
}
