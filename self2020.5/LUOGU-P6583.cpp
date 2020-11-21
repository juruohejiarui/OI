#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

LL n;
inline LL f(LL a) { return a - (a/2) - (a/5) + (a/10); }
inline LL g(LL a) {
    LL ret = 0;
    for (LL p2 = 1; p2 <= a; p2 *= 2)
        for (LL p5 = 1; p2 * p5 <= a; p5 *= 5)
            ret++;
    return ret;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%lld\n", &n);
    LL ans = 0;
    for (LL l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (f(r) - f(l - 1)) * (n / l) * g(n / l);
    }
    printf("%lld\n", ans);
    return 0;
}