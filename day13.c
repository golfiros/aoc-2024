#include <stdio.h>
#include <stdlib.h>

/*
struct d {
  int r, a, b;
} d(int a, int b) {
  int sa = a < 0, sb = b < 0;
  if (sa)
    a = -a;
  if (sb)
    b = -b;
  struct d d0 = {a, 1, 0}, d1 = {b, 0, 1};
  while (d1.r) {
    int q = d0.r / d1.r;
    struct d d = {
        d0.r - q * d1.r,
        d0.a - q * d1.a,
        d0.b - q * d1.b,
    };
    d0 = d1;
    d1 = d;
  }
  if (sa)
    d0.a = -d0.a;
  if (sb)
    d0.b = -d0.b;
  return d0;
}
*/

int main(int argc, char **argv) {
  int xa, xb, ya, yb;
  long long x, y, m = 0, n = 0;

  while (scanf(" Button A: X+%d, Y+%d", &xa, &ya) > 0 &&
         scanf(" Button B: X+%d, Y+%d", &xb, &yb) > 0 &&
         scanf(" Prize: X=%lld, Y=%lld", &x, &y) > 0) {
    // apparently the solutions to all cases are unique and positive and i find
    // that boring as it's just trivial linalg and basically no number theory
    // except row reduction has to be unimodular
    int d[2][4] = {{xa, ya, 1, 0}, {xb, yb, 0, 1}};
    while (d[0][0] && d[1][0]) {
      int i, j;
      if (abs(d[0][0]) > abs(d[1][0]))
        i = 0, j = 1;
      else
        i = 1, j = 0;
      int k = d[i][0] / d[j][0];
      for (int l = 0; l < 4; l++)
        d[i][l] -= d[j][l];
    }
    if (d[1][0])
      for (int i = 0; i < 4; i++) {
        int t = d[1][i];
        d[1][i] = d[0][i];
        d[0][i] = t;
      }
    if (!(x % d[0][0])) {
      long long kx = x / d[0][0];
      if (!((y - kx * d[0][1]) % d[1][1])) {
        long long ky = (y - kx * d[0][1]) / d[1][1];
        long long na = kx * d[0][2] + ky * d[1][2];
        long long nb = kx * d[0][3] + ky * d[1][3];
        m += 3 * na + nb;
      }
    }
    x += 10000000000000;
    y += 10000000000000;
    if (!(x % d[0][0])) {
      long long kx = x / d[0][0];
      if (!((y - kx * d[0][1]) % d[1][1])) {
        long long ky = (y - kx * d[0][1]) / d[1][1];
        long long na = kx * d[0][2] + ky * d[1][2];
        long long nb = kx * d[0][3] + ky * d[1][3];
        n += 3 * na + nb;
      }
    }
  }
  printf("minimum tokens: %lld\n", m);
  printf("corrected tokens: %lld\n", n);
}
