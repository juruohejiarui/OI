#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e6 + 5;

char str[maxn << 1];
int d[maxn << 1], str_len;

struct Query {
    int arg, pos;
    Query(int arg, int pos) : arg(arg), pos(pos) {}
};
vector<Query> q[maxn << 1];

LL C[maxn << 1];

#define lowbit(x) ((x) & -(x))
void change(int x, int val) {
    for (; x <= str_len; x += lowbit(x)) 
        C[x] += val;
}
LL query(int x) {
    LL ret = 0;
    for (; x; x -= lowbit(x)) ret += C[x];
    return ret;
}

void manacher() {
    int r = 0, p = 0;
    for (int i = 1; i <= str_len; i++) {
        if (i > r)
            for (; str[i - d[i] - 1] == str[i + d[i] + 1]; d[i]++) ;
        else {
            int j = p - (i - p);
            if (r - i + 1 > d[j] + 1) d[i] = d[j];
            else {
                d[i] = r - i;
                for (; str[i - d[i] - 1] == str[i + d[i] + 1]; d[i]++) ;
            }
        }
        if (i + d[i] > r) r = d[i] + i, p = i;
        if (str[i] == '#')
            q[i].push_back(Query(1, i)),
            q[i + d[i]].push_back(Query(-1, i));
    }
}

void debug() {
    for (int i = 1; i <= str_len; i++) putchar(str[i]), putchar(' ');
    putchar('\n');
    for (int i = 1; i <= str_len; i++) printf("%d ", d[i]);
    putchar('\n');
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    string s; cin >> s;
    str[0] = '&', str[str_len = 1]= '#';
    for (int i = 0; i < s.size(); i++) 
        str[++str_len] = s[i], str[++str_len] = '#';
    str[str_len + 1] = '$';
    manacher();

    // debug();

    for (int i = 1; i <= str_len; i++) if (str[i] == '#') change(i - d[i], 1);
    LL ans = 0;
    for (int i = 1; i <= str_len; i++) if (str[i] == '#') {
        change(i - d[i], -1);
        for (int j = 0; j < q[i].size(); j++) {
            ans += q[i][j].arg * query(q[i][j].pos);
            // printf("(%d, %d, %d) -> %lld\n", i, q[i][j].arg, q[i][j].pos, ans);
        }
    }
    printf("%lld\n", ans);
    return 0;
}