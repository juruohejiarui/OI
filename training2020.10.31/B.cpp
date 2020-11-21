#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e6 + 5;
int n, f[maxn]; char str[maxn];

void solve() {
    scanf("%s", str + 1), n = strlen(str + 1);
    if (str[1] == '0') {
        printf("-1\n");
        return ;
    }
    int l = 0, r = 2 * n;
    
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}