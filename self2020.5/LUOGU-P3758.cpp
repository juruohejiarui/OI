#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 105;
const LL MOD = 2017;

struct Matrix {
    LL v[maxn][maxn], sz;

    Matrix() { sz = 0, memset(v, 0, sizeof(v)); }
    void load_array(LL arr[][maxn], int arr_sz) {
        arr_sz = sz;
        for (int i = 1; i <= sz; i++)
            for (int j = 1; j <= sz; j++)
                v[i][j] = arr[i][j];
    }
    inline void copy_to(Matrix* m) {
        m->load_array(v, sz);
    }    
};

Matrix operator * (Matrix a, Matrix b) {
    Matrix c; c.sz = max(a.sz, b.sz);
    for (int i = 1; i <= a.sz; i++)
        for (int j = 1; j <= a.sz; j++) 
            for (int k = 1; k <= a.sz; k++)
                c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j] % MOD) % MOD;
    return c;
}
Matrix operator ^ (Matrix a, int b) {
    Matrix c; c.sz = a.sz;
    for (int i = 1; i <= c.sz; i++) c.v[i][i] = 1;
    while (b) {
        if (b & 1) c = c * a;
        a = a * a, b >>= 1;
    }
    return c;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    Matrix matrix; 
    LL ans = 0;
    int n, m, t; scanf("%d%d", &n, &m);
    matrix.sz = n + 1;
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        matrix.v[a][b] = matrix.v[b][a] = 1; 
    }
    for (int i = 1; i <= n + 1; i++)
        matrix.v[i][i] = 1, matrix.v[i][n+1] = 1;
    scanf("%d", &t);
    matrix = matrix ^ t;
    for (int i = 1; i <= n + 1; i++)
        ans = (ans + matrix.v[1][i]) % MOD;
    printf("%lld\n", ans);
    return 0;
}