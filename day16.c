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

static inline struct n {
  int u, v, d, g, i;
  struct n *l, *r;
} *f(struct n **r, int u, int v, int d) {
  struct n *x = *r, *y = NULL;
  while (x) {
    y = x;
    if (u < x->u || (u == x->u && v < x->v) ||
        (u == x->u && v == x->v && d < x->d))
      x = x->l;
    else if (u > x->u || (u == x->u && v > x->v) ||
             (u == x->u && v == x->v && d > x->d))
      x = x->r;
    else
      return x;
  }
  x = malloc(sizeof(*x));
  *x = (struct n){.u = u, .v = v, .d = d, .g = 1 << 30, .i = -1};
  if (y) {
    if (u < y->u || (u == y->u && v < y->v) ||
        (u == y->u && v == y->v && d < y->d))
      y->l = x;
    else
      y->r = x;
  } else
    *r = x;
  return x;
}

struct h {
  int s, u, v, d;
};

static inline void sw(struct h *h, struct n *t, int i, int j) {
  struct h k = h[i];
  h[i] = h[j];
  h[j] = k;
  f(&t, h[i].u, h[i].v, h[i].d)->i = i;
  f(&t, h[j].u, h[j].v, h[j].d)->i = j;
}

static inline void su(struct h *h, struct n *t, int n) {
  int i = n - 1;
  while (i > 0) {
    int p = (i - 1) / 2;
    if (h[p].s < h[i].s)
      break;
    sw(h, t, p, i);
    i = p;
  }
}

static inline void sd(struct h *h, struct n *t, int n) {
  int i = 0;
  while (1) {
    int l = 2 * i + 1, r = 2 * i + 2, c = i;
    if (l < n && h[l].s < h[c].s)
      c = l;
    if (r < n && h[r].s < h[c].s)
      c = r;
    if (c == i)
      break;
    sw(h, t, c, i);
    i = c;
  }
}

static int du[] = {1, 0, -1, 0};
static int dv[] = {0, 1, 0, -1};

int main(int argc, char **argv) {
  int m[256][256], x = 0, y = 0, u, v, u0, v0;
  char str[256];
  while (fgets(str, sizeof(str), stdin)) {
    for (x = 0; str[x] != '\n'; x++)
      switch (str[x]) {
      case '#':
        m[x][y] = 1;
        break;
      case 'S':
        u = x, v = y;
        break;
      case 'E':
        u0 = x, v0 = y;
        break;
      }
    y++;
  }
  struct h h[256] = {{.u = u, .v = v}};
  struct n *t = NULL, *tn = f(&t, u, v, 0);
  tn->g = 0, tn->i = 0;
  int n = 1, c = 0;
  while (!c && n) {
    int u = h[0].u, v = h[0].v, d = h[0].d;
    if (u == u0 && v == v0)
      c = h[0].s;
    else {
      h[0] = h[--n], sd(h, t, n);
      for (int r = 0; r < 4; r++) {
        int g;
        if (r == d) {
          int un = u + du[d], vn = v + dv[d];
          if (m[un][vn])
            continue;
          tn = f(&t, un, vn, d);
          g = f(&t, u, v, d)->g + 1;
        } else if (abs(r - d) == 2)
          continue;
        else {
          tn = f(&t, u, v, r);
          g = f(&t, u, v, d)->g + 1000;
        }
        if (g < tn->g) {
          int f = g + abs(tn->u - u0) + abs(tn->v - v0);
          tn->g = g;
          if (tn->i < 0)
            tn->i = n++;
          h[tn->i] = (struct h){.s = f, .u = tn->u, .v = tn->v, .d = tn->d};
          su(h, t, tn->i + 1);
        }
      }
    }
  }
  printf("minimum score: %d\n", c);
  int b[256][256];
  for (int d0 = 0; d0 < 4; d0++) {
    h[0] = (struct h){.s = c, .u = u0, .v = v0, .d = d0}, n = 1;
    while (n) {
      int s = h[--n].s, u = h[n].u, v = h[n].v, d = h[n].d;
      b[u][v] = 1;
      for (int r = 0; r < 4; r++)
        if (r == d) {
          int un = u - du[d], vn = v - dv[d];
          if (f(&t, un, vn, d)->g == s - 1)
            h[n++] = (struct h){.s = s - 1, .u = un, .v = vn, .d = d};
        } else if (abs(r - d) == 2)
          continue;
        else if (f(&t, u, v, r)->g == s - 1000)
          h[n++] = (struct h){.s = s - 1000, .u = u, .v = v, .d = r};
    }
  }
  T(t, x, free(x));
  c = 0;
  for (int j = 0; j < y; j++)
    for (int i = 0; i < x; i++)
      c += b[i][j];
  printf("number of seats: %d\n", c);
}
