#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main(int argc, char **argv) {
  int n = 0;
  int l[1000], r[1000];
  for (int *pl = l, *pr = r; scanf("%d %d\n", pl, pr) > 0; pl++, pr++, n++)
    ;

  qsort(l, n, sizeof(*l), cmp);
  qsort(r, n, sizeof(*r), cmp);

  int t = 0, s = 0;
  for (int i = 0; i < n; i++) {
    t += abs(l[i] - r[i]);
    int *pl = bsearch(l + i, r, n, sizeof(*r), cmp);
    if (!pl)
      continue;
    int *pr = pl;
    while (l[i] == *(pl - 1))
      pl--;
    while (l[i] == *pr)
      pr++;
    s += l[i] * (pr - pl);
  }
  printf("total distance: %d\n", t);
  printf("total similarity: %d\n", s);
}
