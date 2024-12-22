#include <stdio.h>
#include <stdlib.h>

static const int du[] = {1, 0, -1, 0}, dv[] = {0, 1, 0, -1};

int main(int argc, char **argv) {
  int m[256][256], d[256][256], x = 0, y = 0, u, v, u0, v0;
  char str[256];
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; x++) {
      d[x][y] = -1;
      switch (str[x]) {
      case '.':
      case 'S':
        m[x][y] = 1;
        break;
        /*
      case 'S':
        u = x, v = y, m[x][y] = 1;
        break;
        */
      case 'E':
        u0 = u = x, v0 = v = y, m[x][y] = 1;
        break;
      }
    }
    y++;
  }

  d[u0][v0] = 0;
  int n = 0;
  while (1) {
    int a = 0;
    for (int k = 0; !a && k < 4; k++)
      if (m[u + du[k]][v + dv[k]] && d[u + du[k]][v + dv[k]] < 0) {
        d[u + du[k]][v + dv[k]] = d[u][v] + 1;
        u = u + du[k], v = v + dv[k];
        a = 1;
      }
    if (!a)
      break;
    int um = u - 2, uM = u + 2;
    for (int i = um; i <= uM; i++) {
      if (i < 0 || i >= x)
        continue;
      int vm = v - 2 + abs(i - u), vM = v + 2 - abs(i - u);
      for (int j = vm; j <= vM; j++) {
        if (j < 0 || j >= y)
          continue;
        int f = abs(i - u) + abs(j - v);
        if (d[i][j] >= 0)
          n += d[u][v] - (d[i][j] + f) >= 100;
      }
    }
  }
  printf("number of 2ps cheats: %d\n", n);

  u = u0, v = v0, n = 0;
  while (1) {
    int a = 0;
    for (int k = 0; !a && k < 4; k++)
      if (d[u + du[k]][v + dv[k]] > d[u][v])
        u = u + du[k], v = v + dv[k], a = 1;
    if (!a)
      break;
    int um = u - 20, uM = u + 20;
    for (int i = um; i <= uM; i++) {
      if (i < 0 || i >= x)
        continue;
      int vm = v - 20 + abs(i - u), vM = v + 20 - abs(i - u);
      for (int j = vm; j <= vM; j++) {
        if (j < 0 || j >= y)
          continue;
        int f = abs(i - u) + abs(j - v);
        if (d[i][j] >= 0)
          n += d[u][v] - (d[i][j] + f) >= 100;
      }
    }
  }
  printf("number of 20ps cheats: %d\n", n);
}
