# 前言
Q：好想你之前写过一个$\mathrm{AC}自动机$啊，怎么又重新写了？

A：主要是因为之前写的东西自己看不懂，就重新写了。

## 符号约定
1. $|S|$表示字符串$S$的长度。
2. 后缀用$\mathrm{Suf}(S,i=\mathrm{Any})$表示，$i$表示开始位置，如果不写$i$则表示后缀集合。
3. $S[i...j]$表示$S$中，开始和结束位置分别为$i$,$j$的子串
4. $\Sigma$表示字符集大小

# AC自动机
## 基本概念
基本的$\mathrm{AC自动机}$包含两个部分：
1. $\mathrm{trie树}$(字典树)
2. $\mathrm{trie树}$每个节点上的$\mathrm{fail}$指针

对于$\mathrm{trie树}$，相信大家都懂（不懂的可以上网看看，非常简单好懂）

对于$\mathrm{fail}$就需要联系到$\mathrm{KMP}$算法了。

### $\mathrm{fail}$指针

在$\mathrm{KMP}$中，$\mathrm{nex}[i]$的定义如下：
$$
\mathrm{nex}[i]=\max_{\mathrm{Suf}(S,j)=S[1,i-j+1]} \{j\}
$$
讲句人话，就是子串$S[1,i]$中最长的完全相同的前缀后缀。

现在我们将其类比到$\mathrm{AC自动机}$中。

用$\mathrm{str}(u)$表示$\mathrm{trie}$中从根节点连接到节点$u$所组成的字符串。

那么$\mathrm{fail}$的定义如下：
$$
\mathrm{fail}(u)=\mathrm{val}
    \max_{\mathrm{str(v)} \in \mathrm{Suf}(u)}
    \{|\mathrm{str}(v)|\}      
$$
也就是在$\mathrm{trie}$中找出$\mathrm{str}(u)$中最长的存在于字典树中的后缀。

可以发现，$\mathrm{KMP}$算法实际上就是$\mathrm{AC}自动机$中的特殊情况：只有一条链。

对于$\mathrm{fail}$指针，有一些和$\mathrm{nex}$相似的特点：
$$
\mathrm{str}(\mathrm{fail}^i (u)) \in \mathrm{Suf}({\mathrm{str}(u)})
$$
解释一下，对于一个函数$f(x)$:
$$
f^i(x)=\underbrace{f(f(f(x)))}_{i个f}\\
例如 f^3(x)=f(f(f(x)))
$$

同时可以证明，节点$u$沿着$\mathrm{fail}$指针往上跳跃，就一定能找到所有存在于字典树中的$\mathrm{str}(u)$后缀。

### $\mathrm{fail}$转移边
这个东西实际上是用来简化代码的。

对于字典树中一个节点$u$, 如果它不存在转移边$c$，那么增加一条转移边$c$，指向$\mathrm{fail}(u)$中沿转移边$c$到达的节点。

## 构建
一个$\mathrm{AC}自动机$的构造是离线的，分成两步进行：
1. 构建$\mathrm{trie}$树。
2. 构建$\mathrm{fail}$指针和特殊的转移边。

对于第一步，就不再讲了。

对于第二步，使用宽搜构建。

就直接放代码吧。
```cpp
struct TreeNode {
    int fail/*失配指针*/, 
        end_id/*所对应的模式串的结尾的编号*/, 
        son[27]/*对应26个小写字母*/;
} node[1000005];

int tot_node;

void insert(string& str, int ind/*第几个模式串*/) {
    int u = 0;
    for (int i = 0; i < str.length(); i++) {
        if (!node[u].son[str[i] - 'a'])
            node[u].son[str[i] - 'a'] = ++tot_node;
        u = node[u].son[str[i] - 'a'];
    }
    node[u].end_id = ind;
}
void build_fail() {
    queue<int> q;

    for (int i = 0; i < 26; i++) if (node[0].son[i])
        node[node[0].son[i]].fail = 0, //长度为1的字符串fail指针一定是指向根节点
        q.push(node[0].son[i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (node[u].son[i])
                node[node[u].son[i]].fail = node[node[u].fail].son[i],//找到该节点的fail，然后向fail节点字符串末尾尝试增加一个字符
                q.push(node[u].son[i]);
            else 
                node[u].son[i] = node[node[u].fail].son[i];//fail转移边
    }
}
```