#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline long long cb(int x, long long a, long long b, long long c) {
  switch (x) {
  case 0:
  case 1:
  case 2:
  case 3:
    return x;
  case 4:
    return a;
  case 5:
    return b;
  case 6:
    return c;
  }
  return -1;
}

int main(int argc, char **argv) {
  long long a, b, c;
  int *pp, pr[32], n;
  scanf(" Register A: %lld", &a);
  scanf(" Register B: %lld", &b);
  scanf(" Register C: %lld", &c);
  {
    char str[32], *sp;
    scanf(" Program: %s", str);
    for (pp = pr, sp = strtok(str, ","); sp; sp = strtok(NULL, ","))
      *pp++ = atoi(sp);
    n = pp - pr, *pp = -1, sp = str;
    for (pp = pr; *pp >= 0; pp++)
      switch (*pp++) {
      case 0:
        a = a >> cb(*pp, a, b, c);
        break;
      case 1:
        b = b ^ *pp;
        break;
      case 2:
        b = cb(*pp, a, b, c) % 8;
        break;
      case 3:
        if (a)
          pp = pr + *pp - 1;
        break;
      case 4:
        b = b ^ c;
        break;
      case 5:
        sp += sprintf(sp, "%lld,", cb(*pp, a, b, c) % 8);
        break;
      case 6:
        b = a >> cb(*pp, a, b, c);
        break;
      case 7:
        c = a >> cb(*pp, a, b, c);
        break;
      }
    if (sp > str)
      sp[-1] = '\n';
    printf("initial output: %s", str);
  }
  int s[512][32] = {{1}, {2}, {3}, {4}, {5}, {6}, {7}}, p = 7, k = 0;
  long long w[16];
  while (p--) {
    a = 0;
    for (long long i = 0, j = 1; i < 32; i++, j *= 8)
      a += j * s[p][i];
    long long a0 = a;
    int r[32], q = 0;
    for (pp = pr; *pp >= 0; pp++)
      switch (*pp++) {
      case 0:
        a = a >> cb(*pp, a, b, c);
        break;
      case 1:
        b = b ^ *pp;
        break;
      case 2:
        b = cb(*pp, a, b, c) % 8;
        break;
      case 3:
        if (a)
          pp = pr + *pp - 1;
        break;
      case 4:
        b = b ^ c;
        break;
      case 5:
        r[q++] = cb(*pp, a, b, c) % 8;
        break;
      case 6:
        b = a >> cb(*pp, a, b, c);
        break;
      case 7:
        c = a >> cb(*pp, a, b, c);
        break;
      }
    if (q <= n) {
      a = 1;
      for (int i = n - q; a && i < n; i++)
        a &= pr[i] == r[i - (n - q)];
      if (a) {
        int m[32];
        for (int i = 0; i < 32; i++)
          m[i] = s[p][i];
        for (int q = p; p < q + 8; p++) {
          s[p][0] = p - q;
          for (int i = 1; i < 32; i++)
            s[p][i] = m[i - 1];
        }
        if (q == n)
          w[k++] = a0;
      }
    }
  }
  a = (1L << 62) - 1;
  for (int i = 0; i < k; i++)
    if (w[i] < a)
      a = w[i];
  printf("min quine: %lld\n", a);
}
