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
    struct n *V(s)[4096], *x = t->l;                                           \
    int V(p);                                                                  \
    if (t->r)                                                                  \
      V(s)[0] = t->r, V(s)[1] = t, V(p) = 2;                                   \
    else                                                                       \
      V(s)[0] = t, V(p) = 1;                                                   \
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
          {                                                                    \
            _;                                                                 \
          }                                                                    \
        } while (0);                                                           \
        x = NULL;                                                              \
      }                                                                        \
    }                                                                          \
  } while (0)

static inline struct n {
  const char k[3];
  struct n *v;
  int p;
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
  x->p = 0, x->v = x->l = x->r = NULL;
  strcpy((char *)x->k, k);
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
  return strcmp((const char *)a, (const char *)b);
}

int main(int argc, char **argv) {
  struct n *t = NULL;
  char a[3], b[3];
  while (scanf(" %[^-]-%s", a, b) > 1)
    g(&(g(&t, a)->v), b), g(&(g(&t, b)->v), a);

  int n = 0;
  T(t, x, {
    struct s {
      int n;
      char p[4][3];
    } s[64] = {};
    struct s q;
    int p = 1;
    strcpy(s[0].p[0], x->k);
    while (p--) {
      if (s[p].n == 3) {
        if (!strcmp(s[p].p[3], x->k)) {
          int a = 0;
          for (int i = 0; i < 3; i++)
            a = a || s[p].p[i][0] == 't';
          n += a;
        }
        continue;
      }
      q = s[p];
      struct n *e = g(&t, q.p[q.n])->v;
      T(e, y, {
        if (!g(&t, y->k)->p) {
          s[p] = q;
          strcpy(s[p].p[++s[p].n], y->k);
          p++;
        }
      });
    }
    x->p = 1;
  });
  printf("3-cycles with t: %d\n", n / 2);
  struct n *sr[512] = {}, *sp[512] = {}, *sx[512] = {};
  int p = 1;
  T(t, x, g(sp, x->k)->p = 1);
  n = 0;
  char s[256];
  while (p--) {
    if (!sp[p] && !sx[p]) {
      int m = 0;
      char k[64][3] = {};
      T(sr[p], x, strcpy(k[m++], x->k); free(x));
      if (m > n) {
        n = m;
        qsort(k, n, sizeof(*k), cmp);
        char *c = s;
        for (int i = 0; i < n; i++)
          if (i)
            c += sprintf(c, ",%s", k[i]);
          else
            c += sprintf(s, "%s", k[i]);
      }
      continue;
    }
    struct n *r0 = sr[p], *p0 = sp[p], *x0 = sx[p];
    T(p0, x, {
      sr[p] = NULL;
      T(r0, y, g(sr + p, y->k));
      g(sr + p, x->k);
      struct n *e = g(&t, x->k)->v;
      sp[p] = NULL;
      sx[p] = NULL;
      T(e, y, {
        if (g(&p0, y->k)->p)
          g(sp + p, y->k)->p = 1;
        if (g(&x0, y->k)->p)
          g(sx + p, y->k)->p = 1;
      });
      x->p = 0;
      g(&x0, x->k)->p = 1;
      p++;
    });
    T(r0, x, free(x));
    T(p0, x, free(x));
    T(x0, x, free(x));
  }
  T(t, x, T(x->v, y, free(y)); free(x));
  printf("lan pass: %s\n", s);
}
