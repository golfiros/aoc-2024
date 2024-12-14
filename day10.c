#include <stdio.h>

int main(int argc, char **argv) {
  int h[64][64], x = 0, y = 0;
  char str[64];
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; x++)
      h[x][y] = str[x] - '0';
    y++;
  }

  int m = 0, n = 0;

  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      if (!h[i][j]) {
        int a[64][64] = {}, u[256] = {i}, v[256] = {j}, p = 1;
        while (p) {
          int i = u[p - 1], j = v[--p];
          if (h[i][j] == 9) {
            n++;
            if (!a[i][j])
              m++, a[i][j] = 1;
            continue;
          }
          if (i > 0 && h[i - 1][j] == h[i][j] + 1)
            u[p] = i - 1, v[p++] = j;
          if (i < x - 1 && h[i + 1][j] == h[i][j] + 1)
            u[p] = i + 1, v[p++] = j;
          if (j > 0 && h[i][j - 1] == h[i][j] + 1)
            u[p] = i, v[p++] = j - 1;
          if (j < y - 1 && h[i][j + 1] == h[i][j] + 1)
            u[p] = i, v[p++] = j + 1;
        }
      }
  printf("total score: %d\n", m);
  printf("total rating: %d\n", n);
}
