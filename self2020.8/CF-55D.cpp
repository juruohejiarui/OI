#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 25;
LL l, r, f[maxn][2521][50];
int mp[2521], lim[maxn], len;

int self_gcd(int a, int b) { return b ? self_gcd(b, a % b) : a; }
int self_lcm(int a, int b) { return a * b / self_gcd(a, b); }

LL dp(int x, int sum, int md, int limit) {
    if (!x) return sum % md == 0;
    if (!limit && f[x][sum][mp[md]] != -1) return f[x][sum][mp[md]];
    LL ret = 0;
    int y = (limit ? lim[x] : 9);
    for (int i = 0; i <= y; i++) {
        ret += dp(x - 1, (sum * 10 + i)%2520, self_lcm(md,max(i,1)), (limit && (i == y)));
    }
    if (!limit) f[x][sum][mp[md]] = ret;
    return ret;
}

LL calc(LL limit) {
    len = 0;
    while (limit) lim[++len] = limit % 10, limit /= 10;
    return dp(len, 0, 1, 1);
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; cin >> T;
    memset(f, -1, sizeof(f));
    int tmp = 0;
    for (int i = 1; i <= 2520; i++) if (2520 % i == 0) {
        mp[i] = ++tmp;
    }
    while (T--) {
        cin >> l >> r;
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}