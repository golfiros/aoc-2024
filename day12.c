#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int m[256][256], d[256][256] = {}, x = 0, y = 0;
  char str[256];
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; x++)
      m[x][y] = str[x] - 'A';
    y++;
  }

  int t = 0, s = 0;
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      if (!d[i][j]) {
        int a = 0, b = 0, c = 0, u[256] = {i}, v[256] = {j}, p = 1,
            e[256][256] = {}, xl = i, xr = i + 1, yl = j, yr = j + 1;
        d[i][j] = 1;
        while (p) {
          int i = u[p - 1], j = v[--p];
          if (i < xl)
            xl = i;
          if (i + 1 > xr)
            xr = i + 1;
          if (j < yl)
            yl = j;
          if (j + 1 > yr)
            yr = j + 1;
          e[i + 1][j + 1] = 1, a++;
          if (i > 0 && m[i - 1][j] == m[i][j]) {
            if (!d[i - 1][j])
              d[i - 1][j] = 1, u[p] = i - 1, v[p++] = j;
          } else
            b++;
          if (i < x - 1 && m[i + 1][j] == m[i][j]) {
            if (!d[i + 1][j])
              d[i + 1][j] = 1, u[p] = i + 1, v[p++] = j;
          } else
            b++;
          if (j > 0 && m[i][j - 1] == m[i][j]) {
            if (!d[i][j - 1])
              d[i][j - 1] = 1, u[p] = i, v[p++] = j - 1;
          } else
            b++;
          if (j < y - 1 && m[i][j + 1] == m[i][j]) {
            if (!d[i][j + 1])
              d[i][j + 1] = 1, u[p] = i, v[p++] = j + 1;
          } else
            b++;
        }
        t += a * b;
        for (int i = xl; i <= xr; i++)
          for (int j = yl; j <= yr; j++)
            c += abs(e[i][j] - e[i + 1][j] - e[i][j + 1] + e[i + 1][j + 1]);
        s += a * c;
      }
  printf("weighed by perimeter: %d\n", t);
  printf("weighed by sides: %d\n", s);
}
