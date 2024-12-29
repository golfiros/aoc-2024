#include <stdio.h>
#include <stdlib.h>

const static int k[][4] = {
    {2, -1, -1, 10}, {4, -1, -1, 2}, {5, 1, 0, 3},   {6, 2, 10, -1},
    {7, -1, 1, 5},   {8, 4, 2, 6},   {9, 5, 3, -1},  {-1, -1, 4, 8},
    {-1, 7, 5, 9},   {-1, 8, 6, -1}, {3, 0, -1, -1},
};

const static int d[][4] = {
    {-1, -1, 2, 4}, {-1, -1, -1, 2}, {0, 1, -1, 3},
    {4, 2, -1, -1}, {-1, 0, 3, -1},
};

int main(int argc, char **argv) {
  int s[5][5][16][8];
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) {
      struct {
        int i, n, s[8], v[5];
      } q[32] = {{.i = i}}, p;
      q[0].v[i] = 1;
      int n = 1 << 30, m = 0;
      for (int pl = 0, pr = 1; pl != pr; pl = (pl + 1) % 32) {
        if (q[pl].n > n)
          break;
        if (q[pl].i == j) {
          n = q[pl].n;
          for (int k = 0; k < n; k++)
            s[i][j][m][k] = q[pl].s[k];
          s[i][j][m][n] = 4;
          s[i][j][m++][n + 1] = -1;
          s[i][j][m][0] = -1;
          continue;
        }
        p = q[pl];
        for (int b = 0; b < 4; b++)
          if (d[p.i][b] >= 0 && !p.v[d[p.i][b]]) {
            q[pr] = p;
            q[pr].i = d[p.i][b];
            q[pr].n++;
            q[pr].s[p.n] = b;
            q[pr].v[q[pr].i] = 1;
            pr = (pr + 1) % 32;
          }
      }
    }

  long long l[26][5][5] = {};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      l[0][i][j] = 1;

  for (int n = 0; n < 25; n++)
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++) {
        long long t = 1L << 62, m;
        for (int k = 0; s[i][j][k][0] != -1; k++) {
          m = l[n][4][s[i][j][k][0]];
          for (int p = 1; s[i][j][k][p] != -1; p++)
            m += l[n][s[i][j][k][p - 1]][s[i][j][k][p]];
          if (t > m)
            t = m;
        }
        l[n + 1][i][j] = t;
      }

  char str[8];
  int b[2] = {2, 25};
  long long c[2] = {};
  while (scanf(" %s", str) > 0) {
    for (int i = 0; i < 4; i++) {
      int s = i ? str[i - 1] - '0' : 10;
      int t = str[i] == 'A' ? 10 : str[i] - '0';
      struct {
        int i, n, s[8], v[11];
      } q[32] = {{.i = s}}, p;
      q[0].v[s] = 1;
      int n = 1 << 30;
      long long m[2] = {1L << 62, 1L << 62};
      for (int pl = 0, pr = 1; pl != pr; pl = (pl + 1) % 32) {
        if (q[pl].n > n)
          break;
        if (q[pl].i == t) {
          n = q[pl].n;
          for (int a = 0; a < 2; a++) {
            long long k = l[b[a]][4][q[pl].s[0]] + l[b[a]][q[pl].s[n - 1]][4];
            for (int i = 1; i < n; i++)
              k += l[b[a]][q[pl].s[i - 1]][q[pl].s[i]];
            if (m[a] > k)
              m[a] = k;
          }
          continue;
        }
        p = q[pl];
        for (int b = 0; b < 4; b++)
          if (k[p.i][b] >= 0 && !p.v[k[p.i][b]]) {
            q[pr] = p;
            q[pr].i = k[p.i][b];
            q[pr].n++;
            q[pr].s[p.n] = b;
            q[pr].v[q[pr].i] = 1;
            pr = (pr + 1) % 32;
          }
      }
      for (int a = 0; a < 2; a++)
        c[a] += m[a] * atoi(str);
    }
  };
  for (int a = 0; a < 2; a++)
    printf("%d level complexity: %lld\n", b[a], c[a]);
}
