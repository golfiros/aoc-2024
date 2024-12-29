#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CC(p, s) p##s
#define C(p, s) CC(p, s)
#define V(p) C(p##_, __LINE__)
#define T(t, x, _)                                                             \
  do {                                                                         \
    if (!t)                                                                    \
      break;                                                                   \
    struct n *V(s)[4096] = {t->r, t}, *x = t->l;                               \
    int V(p) = 2;                                                              \
    while (V(p)) {                                                             \
      while (x) {                                                              \
        if (x->r)                                                              \
          V(s)[V(p)++] = x->r;                                                 \
        V(s)[V(p)++] = x;                                                      \
        x = x->l;                                                              \
      }                                                                        \
      x = V(s)[--V(p)];                                                        \
      if (V(p) && x->r && V(s)[V(p) - 1] == x->r) {                            \
        V(s)[V(p) - 1] = x;                                                    \
        x = x->r;                                                              \
      } else {                                                                 \
        do {                                                                   \
          _;                                                                   \
        } while (0);                                                           \
        x = NULL;                                                              \
      }                                                                        \
    }                                                                          \
  } while (0)

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
  T(r, x, free((void *)x->k); free(x));
  printf("total feasible: %d\n", n);
  printf("total ways: %lld\n", u);
}
