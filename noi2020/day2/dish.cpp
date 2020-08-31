#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 5e2 + 5, maxm = 5e3 + 5;

int read_int() {
    int t = 0, m = 1; char ch = getchar();
    while ('0' > ch || ch > '9') ch = getchar();
    while ('0' <= ch && ch <= '9') 
        t = (t << 3) + (t << 1) + ch - '0',
        ch = getchar();
    return t * m;
}

struct Ans {
    int a, x, b, y, cnt;
    void output() {
        if (cnt == 1) printf("%d %d", a, x);
        else printf("%d %d %d %d", a, x, b, y);
    }
} ans[maxm];
int T, succ, tmp[maxn], d[maxn], n, m, k;


namespace Subtask1 {
    void dfs(int x) {
        if (x > m) {
            succ = 1;
            return ;
        }
        for (int i = 1; i <= n; i++) if (d[i]) {
            if (d[i] >= k) {
                ans[x].cnt = 1, ans[x].a = i, ans[x].x = k;
                d[i] -= k;
                dfs(x + 1);
                if (succ) return ;
                d[i] += k;
            } else {
                for (int j = 1; j <= n; j++) if (j != i) {
                    if (d[i] + d[j] < k) continue;
                    int tmp = d[i];
                    ans[x].cnt = 2;
                    ans[x].a = i, ans[x].x = d[i];
                    ans[x].b = j, ans[x].y = k - d[i];
                    d[j] -= k - d[i], d[i] = 0;
                    dfs(x + 1);
                    if (succ) return ;
                    d[i] = tmp, d[j] += k - tmp;
                }
            }
        }
    }
}
namespace Subtask2 {
    void dfs(int x) {
        if (x > m) {
            succ = 1;
            return ;
        }
        int minpos = -1;
        for (int i = 1; i <= n; i++) if (d[i] > 0) {
            if (minpos == -1 || d[minpos] > d[i])
                minpos = i; 
        }
        if (d[minpos] >= k) {
            ans[x].cnt = 1, ans[x].a = minpos, ans[x].x = min(d[minpos], k);
            d[minpos] -= k, dfs(x + 1);
            if (succ) return ;
        } else {
            for (int i = 1; i <= n; i++) if (d[i] > 0 && i != minpos) {
                if (d[i] < k - d[minpos]) continue;
                ans[x].cnt = 2;
                ans[x].a = minpos, ans[x].x = d[minpos];
                ans[x].b = i, ans[x].y = k - d[minpos];
                int tmp = d[minpos];
                d[i] -= k - d[minpos], d[minpos] = 0;
                dfs(x + 1);
                if (succ) return ;
                d[minpos] = tmp, d[i] += k - tmp;
            }
        }
    }
}


void solve(int id) {
    n = read_int(), m = read_int(), k = read_int();
    for (int i = 1; i <= n; i++) tmp[i] = d[i] = read_int();
    succ = 0;
    if (n < 5) Subtask1::dfs(1);
    else Subtask2::dfs(1);
    if (!succ) { printf("-1\n"); }
    else {
        for (int i = 1; i <= m; i++) ans[i].output(), putchar('\n');
        
        // printf("\n\n");
        // for (int i = 0; i <= m; i++) {
        //     tmp[ans[i].a] -= ans[i].x, tmp[ans[i].b] -= ans[i].y;
        //     for (int j = 1; j <= n; j++) 
        //         printf("\t%d ", tmp[j]);
        //     putchar('\n');
        // }
    }
}

int main() {
    // freopen("dish.in", "r", stdin);
    // freopen("dish.out", "w", stdout);
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    T = read_int();
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}