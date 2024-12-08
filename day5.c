#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int g[128][128] = {}, t = 0, u = 0, i, j;
  char str[256];
  while (fgets(str, sizeof(str), stdin) && sscanf(str, "%d|%d", &i, &j) > 0)
    g[i][j] = 1;
  while (fgets(str, sizeof(str), stdin)) {
    int m = 0, n[32];
    for (char *p = strtok(str, ","); p; p = strtok(NULL, ","))
      n[m++] = atoi(p);

    int d[32];
    for (i = 0; i < m; i++)
      for (j = 0; j < m; j++)
        d[i] += g[n[j]][n[i]];

    int s[32], sp = 0;
    for (i = 0; i < m; i++)
      if (!d[i])
        s[sp++] = i;

    int l[32], lp = 0;
    while (sp) {
      i = l[lp++] = s[--sp];
      for (j = 0; j < m; j++)
        if (g[n[i]][n[j]] && !--d[j])
          s[sp++] = j;
    }

    int v = 1;
    for (i = 0; v && i < m; i++)
      v &= l[i] == i;

    t += v * n[m / 2];
    u += !v * n[l[m / 2]];
  }
  printf("sum of correct: %d\n", t);
  printf("sum of corrected: %d\n", u);
}
