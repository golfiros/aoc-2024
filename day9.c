#include <stdio.h>

static inline void sw(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static inline void su(int *h, int n) {
  int i = n - 1;
  while (i > 0) {
    int p = (i - 1) / 2;
    if (h[p] < h[i])
      break;
    sw(h + p, h + i);
    i = p;
  }
}

static inline void sd(int *h, int n) {
  int i = 0;
  while (1) {
    int l = 2 * i + 1, r = 2 * i + 2, c = i;
    if (l < n && h[l] < h[c])
      c = l;
    if (r < n && h[r] < h[c])
      c = r;
    if (c == i)
      break;
    sw(h + c, h + i);
    i = c;
  }
}

int main(int argc, char **argv) {
  char str[32768];
  fgets(str, sizeof(str), stdin);
  int n, a[16384], b[16384], c[16384], h[16][8192], ph[16] = {};
  for (int m = 0, i = 0; str[m] != '\n' || !(n = m); i += str[m] - '0', m++)
    if (m % 2) {
      int j = str[m] - '0';
      h[j][ph[j]++] = i, su(h[j], ph[j]);
      c[m / 2] = j;
    } else
      a[m / 2] = i, b[m / 2] = str[m] - '0';
  n = n / 2 + 1;
  long long s = 0;
  int l = 0, r = n, ls = 0, rs = 0, p = 0;
  while (l < r)
    if (!ls) {
      s += ((long long)b[l] * (2 * p + b[l] - 1)) / 2 * l;
      p += b[l];
      ls = c[l++];
    } else if (!rs)
      rs = b[--r];
    else
      ls--, rs--, s += r * p++;
  while (rs--)
    s += r * p++;
  printf("fragged: %lld\n", s);

  s = 0;
  for (int i = n - 1; i >= 0; i--) {
    int k = 0, p = a[i];
    for (int l = b[i]; l < sizeof(ph) / sizeof(*ph); l++)
      if (ph[l] && h[l][0] < p)
        k = l, p = h[l][0];
    if (k) {
      h[k][0] = h[k][--ph[k]], sd(h[k], ph[k]);
      int l = k - b[i];
      h[l][ph[l]++] = p + b[i], su(h[l], ph[l]);
    }
    s += ((long long)b[i] * (2 * p + b[i] - 1)) / 2 * i;
  }
  printf("defragged: %lld\n", s);
}
