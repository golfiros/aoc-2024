#include <stdio.h>

static const char f[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char **argv) {
  char str[256];
  int a[256][256], x, y = 0;
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; a[x][y] = str[x] == '.' ? 0 : str[x], x++)
      ;
    y++;
  }
  int n[256][256] = {}, m[256][256] = {};
  for (const char *p = f; *p; p++) {
    int u0[256] = {}, v0[256] = {}, k = 0;
    for (int i = 0; i < x; i++)
      for (int j = 0; j < x; j++)
        if (a[i][j] == *p)
          u0[k] = i, v0[k++] = j;
    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++) {
        if (i == j) {
          m[u0[i]][v0[j]] = 1;
          continue;
        }
        int u, v;
        u = 2 * u0[i] - u0[j];
        v = 2 * v0[i] - v0[j];
        if (u >= 0 && u < x && v >= 0 && v < y)
          n[u][v] = 1;
        while (u >= 0 && u < x && v >= 0 && v < y)
          m[u][v] = 1, u += u0[i] - u0[j], v += v0[i] - v0[j];
      }
  }
  int t = 0, s = 0;
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      t += n[i][j], s += m[i][j];
  printf("nearby nodes: %d\n", t);
  printf("total nodes: %d\n", s);
}
