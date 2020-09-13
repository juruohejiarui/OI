# FFT

这个东西比较复杂，可能需要看得久一点，而且本人写的比较草率，极有可能让大家看不懂。

## 问题

现在我们需要解决一个加法卷积问题：

已知两个数组$f,g$，每个值为**实数**，大小都为$n$,现在需要求出一个新的数组$h$，大小为$2n$，其中$h_i$用如下方式计算：
$$
h_i=\sum\limits_{j=0}^i g_j f_{i-j}
$$
显然这时时间复杂度是$O(n^2)$的，非常不优秀。需要我们进行优化。

## 引入FFT

仔细看这个加法卷积，可以发现，$f,g$可以看成两个次数为$n-1$的多项式的系数序列（次数从$0$到$n-1$），$h$实际上就是两个多项式乘起来之后得到的新多项式的系数序列。而强大的FFT就是用来求出这样的系数序列的工具。

## 讲解FFT

### 复数

这个东西是高中的内容，不过内容很容易理解，不必担心。

在生活中，我们绝大多数运算都是使用实数的，但是在初中学习开根的时候，我们知道一个特点：$\sqrt{n}$只有在$n\ge 0$的时候才有意义。这就很迷，因为我们不知道$n<0$的时候怎么搞，但是直觉告诉我们，这东西很有可能是存在的。

到了高中我们就知道，这个东西，实际上是一个虚数。

用一个字母$i$表示$\sqrt{-1}$，这个$i$满足已知的各种加减乘除之类的运算，那么对于$\sqrt{n}(n<0)$，就可以表示为$i\sqrt{-n}$。

将实数和虚数混合就是复数，一个复数用一个二元组$(a,b)$表示（是不是很像坐标，实际上可以看成坐标），它表示$a+bi$这样一个一部分存在，一部分不存在的数，复数也满足已知的各种运算。

这样就能解释当初我们学一元二次方程求解时所谓的无解问题了：实际上无解的意思是在实数域上无解，所有的解在复数域上。

接下来说一下复数的四则运算：

**加法**：$(a,b)+(c,d)=(a+c,b+d)$，对应相加，简单好懂。

**减法**：$(a,b)-(c,d)=(a-c,b-d)$，对应相减

**乘法**：$(a,b)\times(c,d)=(a+bi)\times(c+di)=ac+bci+adi+bdi^2=(ac-bd,bc+ad)$，多项式乘法搞一搞就行了。

**除法**：
$$
\frac{(a,b)}{(c,d)}
=\frac{a+bi}{c+di}
=\frac{(a+bi)(c-di)}{(c+di)(c-di)}
=\frac{ac+bci-adi+bd}{c^2-d^2}
=(\frac{ac+bd}{c^2-d^2},\frac{bd+ad}{c^2-d^2})
$$
这个和根式的分母有理化非常像，就是要将分母中的$i$消去。

总的来说，复数的加减乘除和多项式的加减乘除没什么区别，也不需要硬记，使用之前写一写就行了。

复数在一般情况下没有比较大小的方法。

### 复平面

之前讲过，一个复数可以看作一个平面上的坐标（以实部$a$作为横坐标，将虚部的$b$作为纵坐标），这样一个表示虚数的平面，我们称为复数平面，简称**复平面**，这个东西可以帮助我们理解复数的各种性质。

首先介绍一下基本概念：

**模长**：一个复数坐标和原点的距离，形式化表示如下：
$$
\overline{A}=\sqrt{a^2+b^2}
$$
**幅角**：将复数点$A$和原点$O$连接得到的线段**顺时针**旋转一定度数$\alpha$之后和$x$轴重合，我们称$\alpha$为该复数点$A$的幅角，这里我们用符号$\alpha(A)$表示复数点$A$的幅角。

现在有两个复数$a,b$，他们在复平面上的对应点分别为$A,B$,现在两个复数相乘，得到一个新的复数$c$,它在平面上的对应点为$C$,那么就会有：
$$
\overline{C}=\overline{A}\times \overline{B}\\
\alpha(C)=\alpha(A)+\alpha(B)
$$
第一个直接硬代数，第二个要用数形结合证明一下，这个留给大佬们证明了。

### DFT和IDFT

对于一个$n$次多项式，共有$n+1$项，如果全都写出来就太麻烦了，所以我们用$F(x)$表示这个多项式，其中$F_i$表示次数为$i$的项的系数。这个是系数表达法。

显然，对于$n+1$个平面上的横坐标不相同的点，可以唯一表示一个$n$次的多项式。

现在我们需要求出两个$n$次多项式$F(x),G(x)$之积$H(x)$，就是$H(x)=F(x)\times G(x)$。现在我们使用点值表达这个多项式（分别表示两个多项式的$i$次项的两个点的横坐标相同，我们称这两个点为一组点），可以发现，将一组点的纵坐标对应相乘得到的新坐标就是多项式点值表达的其中一个。而现在我们只能得到$n+1$个点，而新的多项式需要$2n+1$个点，所以我们需要额外增加$n$个，也就是说，$H$的点值表达就是：
$$
(x_0,Fy_0\times Gy_0),(x_1,Fy_1\times Gy_1)...(x_{2n-1},Fy_{2n-1}\times Gy_{2n-1}),(x_{2n},Fy_{2n}\times Gy_{2n})
$$
我们称将多项式的系数表达法转化为点值表达法的过程为``DFT``，称将点值表达法转化为系数表达法的过程为``IDFT``，可以发现，这两个运算互为逆运算。

而``FFT``实际上，就是``DFT``$\rightarrow$点值相乘$\rightarrow$``IDFT``

但是我们平常用的实数没有什么好性质可以用于快速转换表达方式，所以需要复数这个奇怪的东西。

### 单位根

在复平面上作一个单位圆，圆心为原点，半径为$1$，那么在这个单位圆上的所有复数，模长都是$1$（废话），根据$1\times1=1$（废话），那么任意两个在单位圆上的复数点所代表的复数相乘，得到的复数所对应的点一定在这个圆上。

而一个$n-1$次多项式的单位根就是满足$x^n=1$的复数$x$。显然，$x$对应的点一定在单位圆上，若要证明，可以将模长和1的大小关系进行分类。

现在假设有$n$个单位根，那么它们的幅角都是$\frac{i}{n}\times 360^\circ(0 \leq i < n, i\in \mathbb{Z})$。

**证明**：因为一个$n$次方程在复数域上有$n$个解，因此单位根的个数为$n$。可以发现，对于一个在单位圆上的复数$a$，用$\alpha$暂时表示其幅角，那么$a^n$对应的幅角就是$n\times\alpha$，那么幅角为$\frac{i}{n}\times 360^\circ$的复数的$n$次方对应的幅角就是$i\times 360^\circ=0^\circ$，那么它的$n$次方等于$1$，证毕。

好了，我们已经证明出了单位根是个什么东西，那么我们来表示单位根吧：

$\omega_n^i$表示$n$次单位根中，幅角为$\frac{i}{n}\times 360$的单位根，其中有一些废话一样的性质，用于初始化：
$$
\omega_n^0=1, \omega_n^i=(\omega_n^1)^k=\omega_n^{i-1}\times \omega_n^1
$$
这样就能得到所有的单位根了。

$i$实际上是一个模$n$下的数，同时根据上面得到的次数和幅角的关系，那么可以得到下面的一些性质：
$$
\begin{aligned}
\omega_n^k &= \omega_n^{k\%n}\\
\omega_{2n}^{2k} &= \omega_n^k\\
\omega_n^j \times \omega_n^k&=\omega_n^{j+k}\\
(\omega_n^j)^k&=\omega_n^{jk}\\
(\omega_n^k)^{-1}&=\omega_n^{-k}=\omega_n^{n-k}\\
以下性质存在的条件是&n\%2=0\\
(\omega_n^{\frac{n}{2}})&=-1\\
(\omega_n^{\frac{n}{2}+k})&=\omega_n^k \times \omega_n^{\frac{n}{2}}=-\omega_n^k
\end{aligned}
$$

### 加速DFT

众所周知，正常情况下多项式的一个点值需要$O(n)$的时间进行计算，而我们需要$n+1$个点值，所以计算出点值表达法的时间复杂度是$O(n^2)$的，非常不优秀。于是我们进行优化。

这里我们只讨论$n$是$2$的整数次幂的情况。

首先对于一个$n-1$次的多项式，我们将其按照次数的奇偶性分成两部分。比如对于一个多项式$F(x)$，将其进行分割：
$$
\begin{aligned}
F(x)&=	\sum\limits_{i=0}^{\frac{n-2}{2}}F_{2i}x^{2i}
			+	\sum\limits_{i=0}^{\frac{n-2}{2}}F_{2i+1}x^{2i+1}\\
		&=  \sum\limits_{i=0}^{\frac{n-2}{2}}F_{2i}x^{2i}
			+	x
				\sum\limits_{i=0}^{\frac{n-2}{2}}F_{2i+1}x^{2i}
\end{aligned}
$$


那么我们就能得到两个次数为$\frac{n}{2}-1$的多项式，分别为$F_l(x),F_r(x)$。

那么原来的多项式可以表达为$F(x)=F_l(x^2)+xF_r(x^2)$

而我们只要将这两个式子求出点值表达就好了。

用$m$表示$\cfrac{n}{2}$，将$\omega_n^k(k<m)$代入到多项式中，接着进行变换：
$$
\begin{aligned}
F(\omega_n^k)
	&=	F_l((\omega_n^k)^2)
		+	\omega_n^k
			F_r((\omega_n^k)^2)\\
	&= 	F_l(\omega_m^k)
		+ \omega_n^k
			F_r(\omega_m^k)\\
\end{aligned}
$$
再将$\omega_n^{k+m}$代入：
$$
\begin{aligned}
F(\omega_n^{k+m})
	&=F_l((\omega_n^{k+m})^2)+\omega_n^{k+m} F_r((\omega_n^{k+m})^2)\\
	&=F_l(\omega_n^{2k+n})-\omega_n^k F_r(\omega_n^{2k+n})\\
	&=F_l(\omega_m^k)-\omega_n^k F_r(\omega_m^k)
\end{aligned}
$$
可以发现，两个代入得到的**右式**只有第二项的正负号是不同的。

现在如果知道了$F_l(x),F_r(x)$在对应位置的点值表达，那么就能较短时间内得到$F(x)$在$\omega_n^0,\omega_n^1...\omega_n^{m-1}$的点值表达，接着得到$\omega_n^{m},\omega_n^{m+1}...\omega_n^{n-1},\omega_n^{n}$的点值表达。

至于$F_l(x),F_r(x)$点值表达的求解方式，可以使用**分治**解决。

### 加速IDFT

现在我们有了点值表达，需要将其转化为系数表达。

这个很简单，其实就是将$\omega_n^k$转化为$\omega_n^{-k}$，然后再除以$n$，就可以了，下面个证明：

设$P$是$F(x)$的点值表达所得到的序列，其中$P_i$表示第$i$个点值，代入的值为$\omega_n^i$,那么可以得到：
$$
P_k=\sum\limits_{i=0}^{n-1}(\omega_n^k)^iF_i\Longrightarrow nF_k=\sum_{i=0}^{n-1}(\omega_n^{-k})^iP_i
$$
将第二条式子右边进行展开：
$$
\begin{aligned}
右式
	&=\sum_{i=0}^{n-1}(\omega_n^{-k})^i\sum\limits_{j=0}^{n-1}(\omega_n^i)^jF_j\\
	&=\sum_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}\omega_n^{i(j-k)}F_j\\
\end{aligned}
$$
可以证明，只有在$j-k=0$的情况下，式子才会出现贡献，所以可以得到第二条式子。

所以现在只需要将$P_i$看作系数表达，将单位根换一下，就可以使用类似的方法求出原多项式的系数表达了。

### 实现

前面只讨论了$n$等于$2$的幂的情况，而如果$n$不是$2$的幂，那么需要将序列用$0$填充，这里需要注意:**开的空间一定要够大**。

因为``DFT,IDFT``只有一点差别，所以使用同一个函数，加一点特判完成。

按照分治的基本方法进行``FFT``，会导致常数非常大，主要原因是**大量的数据拷贝**，我们需要想办法去掉这个累赘。

考虑序列中每一个元素分治到最底层时候的位置，可以得到每一个初始位置和最终位置的规律，用递推式表达：
$$
lsp(i)=\frac{lsp(\frac{i}{2})}{2}+[i\%2==1]\times\frac{n}{2}
$$
由于乘法和除法消耗时间过大，所以使用位运算和三目运算符代替。

这样就可以避免在分治子问题的时候进行拷贝了

还有就是合并的时候的优化，将运算顺序调换一下，直接看代码吧（可以A掉[模版题](https://www.luogu.com.cn/problem/P3803)）。

```cpp
#include <bits/stdc++.h>
#define NUM double

using namespace std;

const int maxn = 1.35e6 + 5;
struct Complex { //复数结构体，常数较大，但是比STL好多了
    NUM x, y;
    Complex(NUM x = 0, NUM y = 0) : x(x), y(y) {}
    friend Complex operator + (Complex a, Complex b) {
        return Complex(a.x + b.x, a.y + b.y);
    }
    friend Complex operator - (Complex a, Complex b) {
        return Complex(a.x - b.x, a.y - b.y);
    }
    friend Complex operator * (Complex a, Complex b) {
        return Complex(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
    }//不需要除法，就不写了
} f[maxn << 1], p[maxn << 1];

NUM self_pi; //常数：圆周率
int n, m, lsp[maxn << 1];

void init() {
    m += n;
    for (n = 1; n <= m; n <<= 1); //将n转化为2^i
    self_pi = acos(-1); //可以得到高精度的圆周率
    for (int i = 0; i < n; i++) lsp[i] = (lsp[i>>1]>>1) | ((i&1)?(n>>1):0); //计算分治最终位置
}

void fft(Complex *f, int flag) {
    for (int i = 0; i < n; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]); //将所有元素移到分治最终位置
    for (int i = 2; i <= n; i <<= 1) {
        int lsl = i >> 1; //子问题的解决的序列长度
        Complex w1(cos(2 * self_pi / i), sin(2 * self_pi / i));//C++的三角函数使用弧度制，360度对应2*pi
        if (!flag) w1.y *= -1; //DFT和IDFT区别
        for (int st = 0; st < n; st += i) {
            Complex buf(1, 0);
            for (int k = st; k < st + lsl; k++) {
                Complex tmp = buf * f[k + lsl]; //合并时候的优化
                f[k + lsl] = f[k] - tmp;
                f[k] = f[k] + tmp;
                buf = buf * w1;
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &p[i].x);
    init();
    fft(f, 1), fft(p, 1); //转化为点值表达
    for (int i = 0; i < n; i++) f[i] = f[i] * p[i]; //乘起来
    fft(f, 0); //转化为系数表达
    for (int i = 0; i <= m; i++) printf("%d ", (int)(f[i].x / n + 0.49)); //常用技巧：四舍五入
    return 0;
}
```

# NTT

## 问题

依然是加法卷积，但是是在模$p$的情况下计算的。

## 引入NTT

显然如果数字过大，``FFT``就显得非常不优秀，主要因为复数的单位根计算使用了浮点数，所以不能进行取模，而我们就需要在模域中找到一个优秀的东西替代单位根，这样的``DFT,IDFT``，就叫做``NTT``

## 讲解NTT

### 原根

首先回顾我们使用了单位根的哪些性质：
1. $(\omega_n^1)^k=\omega_n^k$
2. $\omega_n^{k\%n}=\omega_n^k$
3. $\omega_{2n}^{2k}=\omega_{n}^{k}$
4. $\omega_{n}^{k+\frac{n}{2}}=-\omega_n^k$
5. $\sum\limits_{i=1}^{n-1}\omega_n^i=0$

一个原根是在模$p$意义下的一个奇怪的数$g$，这个模数$p$可以表示为$k2^t+1$。

而原根$g$满足$g^{0}～g^{p-1}$都不相同。

现在用原根表示一个单位根，即：
$$
\omega_n^1=g^{\frac{p-1}{n}}
$$
那么，对于显然单位根的第一条性质，原根也是可以满足的。
现在对其他四条性质也证明一下：

### 性质2
$$
\omega_n^{k}=(g^{\frac{p-1}{n}})^{k}=g^{k\frac{p-1}{n}}
$$
根据费马小定理，进行一些简单的变换：
$$
\begin{aligned}
g^{k\frac{p-1}{n}}  
    &=g^{\frac{k}{n}\%1\times(p-1)}\\
    &=g^{\frac{k\%n}{n}\times(p-1)}\\
    &=(g^{\frac{p-1}{n}})^{k\%n}\\
    &=\omega_n^{k\%n}
\end{aligned}
$$
### 性质3
$$
\begin{aligned}
\omega_{2n}^{2k}
    &=(g^{\frac{p-1}{2n}})^{2k}\\
    &=g^{(p-1)\times\frac{2k}{2n}}\\
    &=g^{\frac{p-1}{n}}
\end{aligned}
$$
### 性质4
$$
\begin{aligned}
\omega_n^{n+\frac{n}{2}}
    &=\omega_n^{k}\times \omega_n^{\frac{n}{2}}\\
    &=\omega_n^{k}\times (-1)\\
    &=-\omega_n^{k}
\end{aligned}
$$
至于为什么$\omega_n^{\frac{n}{2}}=-1$而不是$1$，则可以根据原根互不相同的原因得到。
### 性质5
这个本质上是一个等比数列求和，可以得到：
$$
\sum_{i=1}^n\omega_n^i=\frac{\omega_n^{n-1}-1}{\omega_n^1-1}=0
$$


可以发现，原根一样可以满足所有需要用到的单位根的性质。那么我们就可以愉快地将``FFT``的代码随手改掉一些，变成``NTT``。

这里安利一下[大佬的原根表](http://blog.miskcoo.com/2014/07/fft-prime-table)（懒人福利）

```cpp
LL f1[maxm << 1], f2[maxm << 1], NTT_g, NTT_invg, invf1_len;
int f1_len, f2_len, lsp[maxm << 1];
void NTT_init() {
    f2_len += f1_len, NTT_g = 3, NTT_invg = qpow(NTT_g, MOD - 2);
    for (f1_len = 1; f1_len <= f2_len; f1_len <<= 1) ;
    invf1_len = qpow(f1_len, MOD - 2);
    for (int i = 0; i < f1_len; i++) lsp[i] = (lsp[i>>1]>>1) | ((i&1)?(f1_len>>1):0);
}
void NTT_calc(LL* f, int len, int flag) {
    for (int i = 0; i < len; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        LL w1 = qpow((flag ? NTT_g : NTT_invg), (MOD - 1) / i);
        int lsl = (i >> 1);
        for (int st = 0; st < len; st += i) {
            LL buf = 1;
            for (int k = st; k < st + lsl; k++) {
                LL tmp = buf * f[k + lsl] % MOD;
                f[k + lsl] = (f[k] - tmp + MOD) % MOD;
                f[k] = (f[k] + tmp) % MOD;
                buf = buf * w1 % MOD;
            }
        }
    }
    if (!flag) for (int i = 0; i < len; i++) f[i] = f[i] * invf1_len % MOD;
}

```