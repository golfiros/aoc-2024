#include <stdio.h>

int main(int argc, char **argv) {
  int n = 0, x[512], y[512], vx[512], vy[512];
  while (scanf(" p=%d,%d v=%d,%d", x + n, y + n, vx + n, vy + n) > 0)
    n++;
  for (int t = 0; t < 100; t++) {
    int b[101][103] = {};
    for (int i = 0; i < n; i++) {
      x[i] = (x[i] + vx[i]) % 101, y[i] = (y[i] + vy[i]) % 103;
      if (x[i] < 0)
        x[i] += 101;
      if (y[i] < 0)
        y[i] += 103;
      b[x[i]][y[i]] = 1;
    }
    char str[256];
    sprintf(str, ".build/%05d.pbm", t);
    FILE *fp = fopen(str, "w");
    fprintf(fp, "P1\n101 103\n");
    for (int j = 0; j < 103; j++) {
      for (int i = 0; i < 101; i++)
        fprintf(fp, "%d", b[i][j]);
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
  long long m[4] = {};
  for (int i = 0; i < n; i++) {
    m[0] += x[i] < 50 && y[i] < 51;
    m[1] += x[i] < 50 && y[i] > 51;
    m[2] += x[i] > 50 && y[i] < 51;
    m[3] += x[i] > 50 && y[i] > 51;
  }
  for (int t = 100; t < 10000; t++) {
    int b[101][103] = {};
    for (int i = 0; i < n; i++) {
      x[i] = (x[i] + vx[i]) % 101, y[i] = (y[i] + vy[i]) % 103;
      if (x[i] < 0)
        x[i] += 101;
      if (y[i] < 0)
        y[i] += 103;
      b[x[i]][y[i]] = 1;
    }
    char str[256];
    sprintf(str, ".build/%05d.pbm", t);
    FILE *fp = fopen(str, "w");
    fprintf(fp, "P1\n101 103\n");
    for (int j = 0; j < 103; j++) {
      for (int i = 0; i < 101; i++)
        fprintf(fp, "%d", b[i][j]);
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
  printf("safety factor: %lld\n", m[0] * m[1] * m[2] * m[3]);
  // looking at the renders we have horizontal events at
  // 64 + 103 * n and vertical events at 15 * 101 * n. they meet at 7892 to form
  // a cute tree :)
}
