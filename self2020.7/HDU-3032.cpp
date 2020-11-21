#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

int n; LL ans;
LL sg(LL x) {
    LL v = x % 4;
    if (!v) return x - 1;
    else if (v == 1 || v == 2) return x;
    else return x + 1;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        for (int i = 1; i <= n; i++) {
            LL a; scanf("%lld", &a);
            ans = ans ^ sg(a);
        }
        if (!ans) printf("Bob\n");
        else printf("Alice\n");
    }
    return 0;
}