#include <stdio.h>

#define step(u, v, d)                                                          \
  do {                                                                         \
    int q = 0;                                                                 \
    switch ((d)) {                                                             \
    case 0:                                                                    \
      if ((v) == 0 || !(q = m[(u)][(v) - 1]))                                  \
        (v)--;                                                                 \
      break;                                                                   \
    case 1:                                                                    \
      if ((u) == x - 1 || !(q = m[(u) + 1][(v)]))                              \
        (u)++;                                                                 \
      break;                                                                   \
    case 2:                                                                    \
      if ((v) == y - 1 || !(q = m[(u)][(v) + 1]))                              \
        (v)++;                                                                 \
      break;                                                                   \
    case 3:                                                                    \
      if ((u) == 0 || !(q = m[(u) - 1][(v)]))                                  \
        (u)--;                                                                 \
      break;                                                                   \
    }                                                                          \
    if (q)                                                                     \
      (d) = ((d) + 1) % 4;                                                     \
  } while (0)

int main(int argc, char **argv) {
  char str[256];
  int m[256][256], x, y = 0, u0, v0, d0;
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; x++)
      switch (str[x]) {
      case '#':
        m[x][y] = 1;
        break;
      case '^':
        u0 = x;
        v0 = y;
        d0 = 0;
        break;
      case '>':
        u0 = x;
        v0 = y;
        d0 = 1;
        break;
      case 'v':
        u0 = x;
        v0 = y;
        d0 = 2;
        break;
      case '<':
        u0 = x;
        v0 = y;
        d0 = 3;
        break;
      }
    y++;
  }

  int u = u0, v = v0, d = d0;
  int p[256][256] = {};
  while (u >= 0 && u < x && v >= 0 && v < y) {
    p[u][v] = 1;
    step(u, v, d);
  }

  int c = 0, k = 0;
  for (u = 0; u < x; u++)
    for (v = 0; v < y; v++) {
      c += p[u][v];
      if ((u == u0 && v == v0) || !p[u][v])
        continue;
      m[u][v] = 1;
      int n = 0;
      int uf = u0, vf = v0, df = d0;
      int us = u0, vs = v0, ds = d0;
      do {
        step(uf, vf, df);
        if (n++ % 2)
          step(us, vs, ds);
      } while (uf >= 0 && uf < x && vf >= 0 && vf < y &&
               !(us == uf && vs == vf && ds == df));
      m[u][v] = 0;
      k += (us == uf && vs == vf && ds == df);
    }

  printf("visited positions: %d\n", c);
  printf("possible obstructions: %d\n", k);
}
