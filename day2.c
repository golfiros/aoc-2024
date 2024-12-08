#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int safe(int *l, int d) {
  int s;
  if (l[0] > l[1])
    s = -1;
  else
    s = 1;
  for (int i = 1; i < d; i++) {
    int t = s * (l[i] - l[i - 1]);
    if (t > 3 || t < 1)
      return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  int m = 0, n = 0;
  char str[256];
  while (fgets(str, sizeof(str), stdin)) {
    int l[16], d = 1;
    char *p = strtok(str, " ");
    l[0] = atoi(p);
    while ((p = strtok(NULL, " ")))
      l[d++] = atoi(p);
    if (safe(l, d)) {
      m++;
      n++;
      continue;
    }
    for (int i = 0; i < d; i++) {
      int t = l[i];
      l[i] = l[0];
      l[0] = t;
      if (safe(l + 1, d - 1)) {
        n++;
        break;
      }
    }
  };
  printf("safe reports: %d\n", m);
  printf("damped reports: %d\n", n);
}
