#include <stdio.h>

int main(int argc, char **argv) {
  int n = 0, r = 0, a[131072] = {}, b[131072] = {};
  for (char c; (c = fgetc(stdin)) != '\n'; n++)
    if (n % 2)
      for (int i = 0; i < c - '0'; i++)
        a[r] = -1, b[r++] = -1;
    else
      for (int i = 0; i < c - '0'; i++)
        a[r] = n / 2, b[r++] = n / 2;
  n = (n + 1) / 2;
  int m = r, l = 0;
  while (l < r)
    if (a[l] != -1)
      l++;
    else if (a[r - 1] == -1)
      r--;
    else
      a[l++] = a[r - 1], a[--r] = -1;
  long long c = 0;
  for (int i = 0; i < m; i++)
    if (a[i] != -1)
      c += i * a[i];
  printf("fragged %lld\n", c);

  r = m;
  while (r) {
    while (b[r - 1] == -1)
      r--;
    int rl;
    for (rl = r; rl && b[rl - 1] == b[r - 1]; rl--)
      ;
    for (l = 0; l < rl; l++) {
      if (b[l] == -1) {
        int lr;
        for (lr = l; b[lr] == -1; lr++)
          ;
        if (lr - l >= r - rl) {
          for (int i = 0; i < r - rl; i++)
            b[l + i] = b[rl + i], b[rl + i] = -1;
          break;
        } else
          l = lr - 1;
      }
    }
    r = rl;
  }
  c = 0;
  for (int i = 0; i < m; i++)
    if (b[i] != -1)
      c += i * b[i];
  printf("defragged %lld\n", c);
}
