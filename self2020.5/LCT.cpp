#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5;

int n, fa[maxn], ch[maxn][2], rev[maxn], val[maxn], xor_s[maxn], stk[maxn];

#define LS(x) (ch[x][0])
#define RS(x) (ch[x][1])
#define GET(x) (ch[fa[x]][1] == x)
#define ISROOT(x) (ch[fa[(x)]][0] != (x) && ch[fa[(x)]][1] != (x))

void push_up(int x) {
    xor_s[x] = xor_s[LS(x)] ^ xor_s[RS(x)] ^ val[x];
}
void push_rev(int x) { swap(LS(x), RS(x)); rev[x] ^= 1; }
void push_down(int x) {
    if (rev[x]) {
        if (LS(x)) push_rev(LS(x));
        if (RS(x)) push_rev(RS(x));
        rev[x] = 0;
    }
}

void rotate(int x) {
    int y = fa[x], z = fa[y], k = GET(x);
    if (!ISROOT(y)) ch[z][ch[z][1] == y] = x;
    ch[y][k] = ch[x][!k], fa[ch[x][!k]] = y;
    ch[x][!k] = y, fa[y] = x, fa[x] = z;
    push_up(x), push_up(y);
}

void splay(int x) {
    int y = x, sz = 0;
    stk[++sz] = y;
    while (!ISROOT(y)) stk[++sz] = fa[y], y = fa[y];
    while (sz) push_down(stk[sz--]);
    while (!ISROOT(x)) {
        int f = fa[x];
        if (!ISROOT(f)) rotate(GET(x) == GET(f) ? f : x);
        rotate(x);
    }
    push_up(x);
}

int access(int x) {
    int p;
    for (p = 0; x; p = x, x = fa[x])
        splay(x), ch[x][1] = p, push_up(x);
    return p;
}

void update(int x) {
    if (!ISROOT(x)) update(fa[x]);
    push_down(x);
}
void make_root(int x) {
    access(x), splay(x), push_rev(x);
}
int find_root(int x) {
    access(x), splay(x);
    while (LS(x)) push_down(x), x = LS(x);
    splay(x);
    return x;
}
void split(int x, int y) {
    make_root(x), access(y), splay(y); 
}
void connect(int x, int y) {
    make_root(x);
    if (find_root(y) == x) return ;
    fa[x] = y;
}
void cut(int x, int y) {
    make_root(x);
    if (find_root(y) == x && fa[y] == x && !ch[y][0]) {
        fa[y] = ch[x][1] = 0;
        push_up(x);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1; i <= m; i++) {
        int t, a, b; scanf("%d%d%d", &t, &a, &b);
        switch (t) {
            case 0 : 
                split(a, b);
                printf("%d\n", xor_s[b]);
                break;
            case 1 :
                connect(a, b);
                break;
            case 2 :
                cut(a, b);
                break;
            case 3 : 
                splay(a); val[a] = b;
                break;
        }
    }
    return 0;
}