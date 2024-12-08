#include <stdio.h>

static inline int cmp(const char *c, const char *s, int n) {
  for (int i = 0; i < n; i++)
    if (c[i] != s[n - 1 - i])
      return 0;
  return 1;
}

int main(int argc, char **argv) {
  int s = 0, t = 0, p = 1;
  char c[16] = {};
  while ((*c = fgetc(stdin)) > 0) {
    if (cmp(c, "mul(", 4)) {
      int a, b, c = 0;
      if (scanf("%d,%d)%n", &a, &b, &c) == 2 && c) {
        s += a * b;
        t += p * a * b;
      }
    } else if (cmp(c, "do()", 4))
      p = 1;
    else if (cmp(c, "don't()", 7))
      p = 0;
    for (int i = sizeof(c) - 1; i >= 1; i--)
      c[i] = c[i - 1];
  }
  printf("sum of mul: %d\n", s);
  printf("conditional: %d\n", t);
}
