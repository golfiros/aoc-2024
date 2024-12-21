#include <stdio.h>

int main(int argc, char **argv) {
  char str[256];
  int x, y = 0, ms[64][64] = {}, ml[128][64] = {}, us, vs, ul, vl;
  while (fgets(str, sizeof(str), stdin) && str[0] != '\n') {
    for (x = 0; str[x] != '\n'; x++)
      switch (str[x]) {
      case '#':
        ms[x][y] = ml[2 * x][y] = ml[2 * x + 1][y] = -1;
        break;
      case 'O':
        ms[x][y] = ml[2 * x][y] = 1;
        break;
      case '@':
        ul = 2 * (us = x), vl = vs = y;
        break;
      }
    y++;
  }

  char c;
  while ((c = fgetc(stdin)) > 0) {
    int du, dv;
    switch (c) {
    case '^':
      du = 0, dv = -1;
      break;
    case '>':
      du = 1, dv = 0;
      break;
    case 'v':
      du = 0, dv = 1;
      break;
    case '<':
      du = -1, dv = 0;
      break;
    default:
      continue;
    }
    int u = us, v = vs;
    do
      u += du, v += dv;
    while (ms[u][v] > 0);
    if (!ms[u][v])
      us += du, vs += dv, ms[u][v] = 1, ms[us][vs] = 0;
    int su[128] = {ul}, sv[128] = {vl}, s = 1;
    int qu[128], qv[128], q = 0, a = 1, b[128][64] = {};
    while (a && s) {
      u = su[--s] + du, v = sv[s] + dv;
      if (ml[u][v] < 0)
        a = 0;
      else {
        if (ml[u][v] > 0 && !b[u][v]) {
          b[u][v] = 1;
          qu[q] = u, qv[q++] = v;
          su[s] = u, sv[s++] = v;
          su[s] = u + 1, sv[s++] = v;
        }
        if (ml[u - 1][v] > 0 && !b[u - 1][v]) {
          b[u - 1][v] = 1;
          qu[q] = u - 1, qv[q++] = v;
          su[s] = u - 1, sv[s++] = v;
          su[s] = u, sv[s++] = v;
        }
      }
    }
    if (a) {
      ul += du, vl += dv;
      for (int i = q - 1; a && i >= 0; i--)
        ml[qu[i]][qv[i]] = 0, ml[qu[i] + du][qv[i] + dv] = 1;
    }
  }
  int n = 0;
  for (int j = 0; j < y; j++)
    for (int i = 0; i < x; i++)
      n += (i + 100 * j) * (ms[i][j] > 0);
  printf("short coords: %d\n", n);
  n = 0;
  for (int j = 0; j < y; j++)
    for (int i = 0; i < 2 * x; i++)
      n += (i + 100 * j) * (ml[i][j] > 0);
  printf("long coords: %d\n", n);
}
