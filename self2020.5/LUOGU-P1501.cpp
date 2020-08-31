#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5;
const LL MOD = 51061;

int stk[maxn], stk_sz;
struct LCT {
    int fa[maxn], ch[maxn][2], rev[maxn];
    LL sz[maxn], lz_add[maxn], lz_mul[maxn], sum[maxn], val[maxn];
    #define LS(x) (ch[(x)][0])
    #define RS(x) (ch[(x)][1])
    #define ISROOT(x) (ch[fa[(x)]][0] != (x) && ch[fa[(x)]][1] != (x))
    #define GET(x) (ch[fa[(x)]][1] == (x)) 

    void push_rev(int x) {
        swap(LS(x), RS(x)), rev[x] ^= 1;
    }
    void push_up(int x) {
        sz[x] = sz[LS(x)] + sz[RS(x)] + 1;
        sum[x] = (sum[LS(x)] + sum[RS(x)] + val[x]) % MOD;
    }
    void push_add(int x, LL add_val) {
        if (!x) return ;
        sum[x] = (sum[x] + add_val * sz[x] % MOD) % MOD;
        val[x] = (val[x] + add_val) % MOD,
        lz_add[x] = (lz_add[x] + add_val) % MOD;
    }
    void push_mul(int x, LL mul_val) {
        if (!x) return ;
        sum[x] = sum[x] * mul_val % MOD,
        val[x] = val[x] * mul_val % MOD,
        lz_add[x] = lz_add[x] * mul_val % MOD,
        lz_mul[x] = lz_mul[x] * mul_val % MOD; 
    }

    void push_down(int x) {
        if (lz_mul[x] != 1) push_mul(LS(x), lz_mul[x]), push_mul(RS(x), lz_mul[x]), lz_mul[x] = 1;
        if (lz_add[x]) push_add(LS(x), lz_add[x]), push_add(RS(x), lz_add[x]), lz_add[x] = 0;
        if (rev[x]) {
            if (LS(x)) push_rev(LS(x));
            if (RS(x)) push_rev(RS(x));
            rev[x] = 0;
        }
    }

    void rotate(int x) {
        int f = fa[x], gf = fa[f], k = GET(x), w = ch[x][!k];
        if (!ISROOT(f)) ch[gf][GET(f)] = x;
        ch[x][!k] = f, ch[f][k] = w;
        if (w) fa[w] = f;
        fa[f] = x, fa[x] = gf;
        push_up(f);
    }
    void splay(int x) {
        int y = x;
        stk[stk_sz = 1] = y;
        while (!ISROOT(y)) stk[++stk_sz] = y = fa[y];
        while (stk_sz) push_down(stk[stk_sz--]);
        while (!ISROOT(x)) {
            int f = fa[x];
            if (!ISROOT(f)) 
                rotate(GET(x) == GET(f) ? f : x);
            rotate(x);
        }
        push_up(x);
    } 
    int access(int x) {
        int ls;
        for (ls = 0; x; ls = x, x = fa[x]) 
            splay(x), ch[x][1] = ls, push_up(x);
        return ls;
    }
    void make_root(int x) {
        access(x), splay(x), push_rev(x);
    }
    void split(int x, int y) {
        make_root(x), access(y), splay(y);
    }
    void link(int x, int y) {
        make_root(x); fa[x] = y;
    }
    void cut(int x, int y) {
        split(x, y), fa[x] = ch[y][0] = 0;
    }
} lct;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) lct.lz_mul[i] = lct.val[i] = 1;
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d\n", &a, &b);
        lct.link(a, b);
    }   
    while (m--) {
        char ch; int a, b, c, d;
        cin >> ch; scanf("%d%d", &a, &b);
        switch (ch) {
            case '+': 
                scanf("%d", &c);
                lct.split(a, b), lct.push_add(b, c);
                break;
            case '-':
                scanf("%d%d", &c, &d);
                lct.cut(a, b), lct.link(c, d);
                break;
            case '*':
                scanf("%d", &c);
                lct.split(a, b), lct.push_mul(b, c);
                break;
            case '/':
                lct.split(a, b);
                printf("%lld\n", lct.sum[b]);
                break;
        }
    }
    return 0;
}