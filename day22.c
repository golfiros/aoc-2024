#include <stdio.h>
#include <stdlib.h>

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

static inline int cmp(int k1[4], int k2[4]) {
  for (int i = 0; i < 4; i++)
    if (k1[i] != k2[i])
      return k1[i] - k2[i];
  return 0;
}

static inline struct n {
  int k[4];
  int v, t;
  struct n *l, *r;
} *g(struct n **r, int k[4]) {
  struct n *x = *r, *y = NULL;
  while (x) {
    y = x;
    if (cmp(k, x->k) < 0)
      x = x->l;
    else if (cmp(k, x->k) > 0)
      x = x->r;
    else
      return x;
  }
  x = malloc(sizeof(*x));
  *x = (struct n){};
  for (int i = 0; i < 4; i++)
    x->k[i] = k[i];
  if (y) {
    if (cmp(k, y->k) < 0)
      y->l = x;
    else
      y->r = x;
  } else
    *r = x;
  return x;
}

int main(int argc, char **argv) {
  long long s, k = 0;
  struct n *t = NULL;
  while (scanf(" %lld", &s) > 0) {
    int p0 = s % 10, d[4];
    for (int i = 0; i < 2000; i++) {
      s = (s ^ (s * 64)) % 16777216;
      s = (s ^ (s / 32)) % 16777216;
      s = (s ^ (s * 2048)) % 16777216;
      int p1 = s % 10;
      for (int i = 1; i < 4; i++)
        d[i - 1] = d[i];
      d[3] = p1 - p0;
      p0 = p1;
      if (i >= 3) {
        struct n *n = g(&t, d);
        if (!n->t) {
          n->t = 1, n->v += p0;
        }
      }
    }
    T(t, x, x->t = 0);
    k += s;
  }
  printf("sum of secrets: %lld\n", k);
  int m = 0;
  T(t, x, if (x->v > m) m = x->v; free(x));
  printf("max bananas: %d\n", m);
}
