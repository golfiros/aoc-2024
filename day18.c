#include <stdio.h>

int main(int argc, char **argv) {
  int x = 70 + 1, y = x, u, v, m[128][128];
  for (int i = 0; i < x; i++)
    m[i + 1][0] = m[i + 1][x + 1] = 1;
  for (int i = 0; i < y; i++)
    m[0][i + 1] = m[y + 1][i + 1] = 1;
  for (int i = 0; i < 1024; i++)
    scanf(" %d,%d", &u, &v), m[u + 1][v + 1] = 1;

  int d[128][128] = {};
  for (int j = 0; j < y + 2; j++)
    for (int i = 0; i < x + 2; i++)
      d[i][j] = -1;
  d[1][1] = 0;

  int qu[128] = {1}, qv[128] = {1}, pl = 0, pr = 1;
  while (pl != pr) {
    int u = qu[pl], v = qv[pl];
    pl = (pl + 1) % 128;
    for (int r = 0; r < 4; r++) {
      int i = u + (int[]){1, 0, -1, 0}[r], j = v + (int[]){0, 1, 0, -1}[r];
      if (!m[i][j] && d[i][j] < 0)
        qu[pr] = i, qv[pr] = j, pr = (pr + 1) % 128, d[i][j] = d[u][v] + 1;
    }
  }
  printf("min distance after 1024: %d\n", d[x][y]);
  while (d[x][y] > 0) {
    scanf(" %d,%d", &u, &v), m[u + 1][v + 1] = 1;
    for (int j = 0; j < y + 2; j++)
      for (int i = 0; i < x + 2; i++)
        d[i][j] = -1;
    d[1][1] = 0;

    int qu[128] = {1}, qv[128] = {1}, pl = 0, pr = 1;
    while (pl != pr) {
      int u = qu[pl], v = qv[pl];
      pl = (pl + 1) % 128;
      for (int r = 0; r < 4; r++) {
        int i = u + (int[]){1, 0, -1, 0}[r], j = v + (int[]){0, 1, 0, -1}[r];
        if (!m[i][j] && d[i][j] < 0)
          qu[pr] = i, qv[pr] = j, pr = (pr + 1) % 128, d[i][j] = d[u][v] + 1;
      }
    }
  }
  printf("first blocking coord: %d,%d\n", u, v);
}
