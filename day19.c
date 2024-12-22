#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline struct n {
  const char *k;
  long long v;
  struct n *l, *r;
} *g(struct n **r, const char *k) {
  struct n *x = *r, *y = NULL;
  while (x) {
    y = x;
    if (strcmp(k, x->k) < 0)
      x = x->l;
    else if (strcmp(k, x->k) > 0)
      x = x->r;
    else
      return x;
  }
  x = malloc(sizeof(*x));
  *x = (struct n){.v = -1};
  strcpy((char *)(x->k = malloc(strlen(k) + 1)), k);
  if (y) {
    if (strcmp(k, y->k) < 0)
      y->l = x;
    else
      y->r = x;
  } else
    *r = x;
  return x;
}

int cmp(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv) {
  char str[256];
  const char *t[512] = {};
  int k = 0, m = 0;
  while (scanf("%[^,\n],", str) > 0) {
    const char *s;
    for (s = str; *s == ' '; s++)
      ;
    if (m < strlen(s))
      m = strlen(s);
    strcpy((char *)(t[k++] = malloc(strlen(s) + 1)), s);
  }
  qsort(t, k, sizeof(*t), cmp);

  int n = 0;
  long long u = 0;
  struct n *r = NULL;
  g(&r, "")->v = 1;
  while (scanf("%s", str) > 0) {
    int l = strlen(str);
    for (const char *c = str + l - 1; c >= str; c--) {
      struct n *n = g(&r, c);
      if (n->v < 0) {
        int s = str + l - c;
        if (s > m)
          s = m;
        n->v = 0;
        for (int i = s; i; i--) {
          char a[16] = {};
          strncpy(a, c, i);
          if (bsearch((const char *[]){a}, t, k, sizeof(*t), cmp))
            n->v += g(&r, c + i)->v;
        }
      }
    }
    u += g(&r, str)->v;
    n += g(&r, str)->v > 0;
  }
  printf("total feasible: %d\n", n);
  printf("total ways: %lld\n", u);
}
