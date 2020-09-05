#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5, INF = 1e9;
int n, m, t[maxn], v[maxn], w[maxn];

char read_ch() {
    char ch = getchar();
    while (ch != 'A' && ch != 'B') ch = getchar();
    return ch;
}

bool fl[maxn];
void calc() {
    int mxv = -INF, ans = 0;
    for (int i = 1; i <= n; i++) 
        if (w[i - 1] == 0) {
            if (t[i] == 1) ans += (fl[i] = (v[i] < mxv));
            else mxv = max(mxv, v[i]);
        } else mxv = -INF;
    mxv = -INF;
    for (int i = n; i >= 1; i--) {
        if (w[i] == 1) {
            if (t[i] == 1) ans += (v[i] < mxv && !fl[i]);
            else mxv = max(mxv, v[i]);
        } else mxv = -INF;
    }
    printf("%d\n", ans);
}
int main() {
    freopen("y.in", "r", stdin);
    freopen("y.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        t[i] = read_ch() == 'A' ? 1 : 2;
        w[i] = 1;
    }
    string str;
    while (m--) {
        cin >> str;
        if (str[0] == 'R') {
            int l, r; scanf("%d%d", &l, &r);
            for (int i = l; i < r; i++) w[i] ^= 1;
        } else {
            int x, y; scanf("%d%d", &x, &y);
            v[x] = y;
        }
        calc();
    }
    return 0;
}