#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#define LL long long

using namespace std;

LL a, w, n, M;
struct Complex {
    Complex(LL x, LL y) : x(x), y(y) {}
    LL x, y;
};

inline Complex mul(Complex a, Complex b) {
    return Complex(a.x*b.x%M + a.y*b.y%M*w%M, a.y*b.x*M+a.x*b.y%M);
}

LL qpow(LL a, LL b, LL M) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % M;
        a = a * a % M, b >>= 1;
    }
    return ret;
}
Complex qpow(Complex a, LL b) {
    Complex ret = Complex(1, 0);
    while (b) {
        if (b & 1) ret = mul(ret, a);
        a = mul(a, a), b >>= 1;
    }
    return ret;
}

void solve() {
    scanf("%lld%lld", &n, &M);
    if (!n) { 
        printf("0\n");
        return ;
    }
    if (M == 2) { printf("1\n"); return ; }
    if (qpow(n, (M - 1) >> 1, M) == M - 1) {
        printf("No root\n");
        return ;
    }
    LL ans, ans1, ans2;
    a = rand() % M;
    while (!a || qpow((a * a - n + M) % M, (M - 1) >> 1, M)) a = rand() % M;
    w = (a * a - n + M) % M;
    ans1 = qpow(Complex(a, 1), (M + 1) >> 1).x;
    ans2 = M - ans1;
    if (ans1 > ans2) swap(ans1, ans2);
    if (ans1 != ans2) printf("%lld %lld\n", ans1, ans2);
    else printf("%lld\n", ans1);
}

int main() {
    srand(time(NULL));
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}