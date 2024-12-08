#include <stdio.h>

int main(int argc, char **argv) {
  int m = 0, n = 0;
  int b[32768];
  int p = 0;
  char c;
  while ((c = fgetc(stdin)) > 0)
    if (c == 'X')
      b[p++] = 0;
    else if (c == 'M')
      b[p++] = 1;
    else if (c == 'A')
      b[p++] = 2;
    else if (c == 'S')
      b[p++] = 3;
    else {
      if (!n)
        n = p;
      m++;
    }
  const int s[] = {1, 1 + n, n, -1 + n, -1, -1 - n, -n, 1 - n};
  const int x[] = {1 + n, 1 - n, -1 - n, -1 + n};
  int t = 0, u = 0;
  for (p = 0; p < n * m; p++) {
    if (b[p] == 0) {
      int i = p / n, j = p % n;
      const int d[] = {
          j < n - 3, j < n - 3 && i < m - 3, i < m - 3, j >= 3 && i < m - 3,
          j >= 3,    j >= 3 && i >= 3,       i >= 3,    j < n - 3 && i >= 3,
      };
      for (int k = 0; k < 8; k++) {
        if (!d[k])
          continue;
        int a = d[k];
        for (int l = 0; l < 4; l++)
          if (b[p + l * s[k]] != l)
            a = 0;
        t += a;
      }
    } else if (b[p] == 2) {
      int i = p / n, j = p % n;
      if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
        continue;
      for (int q = 0; q < 4; q++)
        u += b[p + x[(0 + q) % 4]] == 1 && b[p + x[(1 + q) % 4]] == 1 &&
             b[p + x[(2 + q) % 4]] == 3 && b[p + x[(3 + q) % 4]] == 3;
    }
  }
  printf("words: %d\n", t);
  printf("x'es: %d\n", u);
}
