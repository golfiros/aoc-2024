#include <stdio.h>
#include <stdlib.h>

#define T(t, x, _)                                                             \
  do {                                                                         \
    if (!t)                                                                    \
      break;                                                                   \
    struct n *s_##__LINE__[4096] = {t->r, t}, *x = t->l;                       \
    int p_##__LINE__ = 2;                                                      \
    while (p_##__LINE__) {                                                     \
      while (x) {                                                              \
        if (x->r)                                                              \
          s_##__LINE__[p_##__LINE__++] = x->r;                                 \
        s_##__LINE__[p_##__LINE__++] = x;                                      \
        x = x->l;                                                              \
      }                                                                        \
      x = s_##__LINE__[--p_##__LINE__];                                        \
      if (p_##__LINE__ && x->r && s_##__LINE__[p_##__LINE__ - 1] == x->r) {    \
        s_##__LINE__[p_##__LINE__ - 1] = x;                                    \
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
  long long k;
  long long v;
  struct n *l, *r;
} *g(struct n **r, long long k) {
  struct n *x = *r, *y = NULL;
  while (x) {
    y = x;
    if (k < x->k)
      x = x->l;
    else if (k > x->k)
      x = x->r;
    else
      return x;
  }
  x = malloc(sizeof(*x));
  *x = (struct n){.k = k};
  if (y) {
    if (k < y->k)
      y->l = x;
    else
      y->r = x;
  } else
    *r = x;
  return x;
}

int main(int argc, char **argv) {
  int i;
  long long m = 0, n = 0;
  struct n *s = NULL, *t = NULL;
  while (scanf(" %d", &i) > 0)
    g(&s, i)->v++, n++;

  long long l[8] = {1};
  long long h[4] = {1};
  for (i = 1; i < 8; i++)
    l[i] = 10 * l[i - 1];
  for (i = 1; i < 4; i++)
    h[i] = 10 * l[7] * h[i - 1];

  for (int b = 0; b < 75; b++) {
    T(s, x, {
      if (!x->v)
        continue;
      long long v = x->v;
      x->v = 0;
      if (b == 25)
        m += v;
      if (!x->k) {
        g(&t, 1)->v += v;
        continue;
      }
      int d;
      for (d = 0; x->k >= l[d & 0b111] * h[d >> 3]; d++)
        ;
      if (d % 2) {
        g(&t, x->k * 2024)->v += v;
        continue;
      }
      d = d / 2;
      long long p = l[d & 0b111] * h[d >> 3];
      g(&t, x->k % p)->v += v;
      g(&t, x->k / p)->v += v;
      n += v;
    });
    struct n *u = t;
    t = s;
    s = u;
  }
  T(s, x, free(x));
  printf("25 blinks: %lld\n", m);
  printf("75 blinks: %lld\n", n);
}
