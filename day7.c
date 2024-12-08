#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(long long t, int n, const int x[]) {
  if (n == 0)
    return t == x[0];
  return (t > x[n] && f(t - x[n], n - 1, x)) ||
         (!(t % x[n]) && f(t / x[n], n - 1, x));
}

int g(long long t, int n, const int x[]) {
  if (n == 0)
    return t == x[0];
  int p = x[n] < 10 ? 10 : x[n] < 100 ? 100 : 1000;
  return (t > x[n] && g(t - x[n], n - 1, x)) ||
         (!(t % x[n]) && g(t / x[n], n - 1, x)) ||
         (t % p == x[n] && g(t / p, n - 1, x));
}

int main(int argc, char **argv) {
  char str[256];
  long long a = 0, b = 0;
  while (fgets(str, sizeof(str), stdin)) {
    char *p = strtok(str, " ");
    long long t = atoll(p);
    int x[16], n = 0;
    while ((p = strtok(NULL, " ")))
      x[n++] = atoi(p);
    a += t * f(t, n - 1, x);
    b += t * g(t, n - 1, x);
  }
  printf("total correct: %lld\n", a);
  printf("total concat: %lld\n", b);
}
