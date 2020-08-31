#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

const int maxn = 1.35e5 + 5;
struct Complex {
    D x, y;
    Complex(D x = 0, D y = 0) : x(x), y(y) {}
    friend Complex operator + (Complex a, Complex b) {
        return Complex(a.x+b.x, a.y+b.y);
    }
    friend Complex operator - (Complex a, Complex b) {
        return Complex(a.x-b.x, a.y-b.y);
    }
    friend Complex operator * (Complex a, Complex b) {
        return Complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
    }
} f1[maxn << 1], f2[maxn << 1], f3[maxn << 1];

D self_pi;
int n, m, lsp[maxn << 1];
void FFT_init() {
    m = n * 2, self_pi = acos(-1);
    for (n = 1; n <= m; n <<= 1) ;
    for (int i = 0; i < n; i++) lsp[i] = (lsp[i>>1]>>1) | ((i&1)?(n>>1):0);
}

void FFT_calc(Complex* f, int flag) {
    for (int i = 0; i < n; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);

    for (int i = 2; i <= n; i <<= 1) {
        int lsl = (i >> 1);
        Complex w1(cos(2 * self_pi / i), sin(2 * self_pi / i));
        if (!flag) w1.y *= -1;
        for (int st = 0; st < n; st += i) {
            Complex buf(1, 0);
            for (int k = st; k < st + lsl; k++) {
                Complex tmp = f[k + lsl] * buf;
                f[k + lsl] = f[k] - tmp;
                f[k] = f[k] + tmp;
                buf = buf * w1;
            }
        }
    }
    if (!flag) for (int i = 0; i < n; i++) f[i].x /= n;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    int tmp = n;
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &f1[i].x), f2[n - i].x = f1[i].x;
        f3[i].x = 1.0 / i / i;
    }
    FFT_init();
    FFT_calc(f1, 1), FFT_calc(f2, 1), FFT_calc(f3, 1);
    for (int i = 0; i < n; i++) f1[i] = f1[i] * f3[i], f2[i] = f2[i] * f3[i];
    FFT_calc(f1, 0), FFT_calc(f2, 0);
    for (int i = 1; i <= tmp; i++) printf("%.3lf\n", f1[i].x - f2[tmp - i].x);
    return 0;
}