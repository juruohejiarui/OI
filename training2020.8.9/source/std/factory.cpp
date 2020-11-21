// standard program for String Factory 2
// programmed by ryz in 11/23/2012
// using Suffix Array(can be replaced by Suffix Tree) and Binary Indexed Trees(can be replaced by Segement Tree)
// An O(nlogn) solution

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

class Binary_Indexed_Trees
{
	#define lobit(x) (x&(-x))
	int s[500100];
	int n;
	
public:	
	void add(int x,int y)
	{
		while (x<=n)	s[x]+=y,x+=lobit(x);
	}
	
	int ask(int x)
	{
		int ret=0;
		while (x)	ret+=s[x],x-=lobit(x);
		return ret;
	}
	
	Binary_Indexed_Trees(int _n)
	{
		n=_n;
	}
}*T;

class Suffix_Array
{
	char *s;
	int n;
	int rank1[1000010],rank2[1000010],sa[1000010],tp1[1000010],tp2[1000010],rank[1000010];
	void getsa()
	{
		memset(rank1,-1,sizeof rank1);
		memset(rank2,-1,sizeof rank2);
		int m=128,i,j,p,*x=rank1,*y=rank2;
		memset(tp1,0,sizeof tp1);
		for (i=0;i<n;i++)	tp1[x[i]=s[i]]++;
		for (i=1;i<m;i++)	tp1[i]+=tp1[i-1];
		for (i=n-1;i>=0;i--)	sa[--tp1[x[i]]]=i; 
		for (j=1,p=1;p<n;j=(j<<1),m=p)
		{
			p=0;
			for (i=n-j;i<n;i++)	y[p++]=i;
			for (i=0;i<n;i++)	if (sa[i]>=j)	y[p++]=sa[i]-j;
			for (i=0;i<n;i++)	tp2[i]=x[y[i]];
			for (i=0;i<m;i++)	tp1[i]=0;
			for (i=0;i<n;i++)	tp1[tp2[i]]++;
			for (i=1;i<m;i++)	tp1[i]+=tp1[i-1];
			for (i=n-1;i>=0;i--)	sa[--tp1[tp2[i]]]=y[i];
			swap(x,y);
			for (p=1,x[sa[0]]=0,i=1;i<n;i++)
				if (y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+j]==y[sa[i]+j])	x[sa[i]]=p-1;
				else x[sa[i]]=p++;
		}
		for (int i=0;i<n;i++)	rank[sa[i]]=i;
	}
	
public:
	Suffix_Array(char *_s)
	{
		s=_s;
		n=strlen(s);
		getsa();
	}
	
	int bsearch(int l,int r,int len,char x)
	{
		int mid;
		while (l<r)
		{
			mid=(l+r)/2;
			if (s[sa[mid]+len]>=x) r=mid;else l=mid+1;
		}
		return l;
	}
	
	pair<int,int> find(char *a)
	{
		int l=0,r=n,m=strlen(a),_l,_r;
		for (int i=0;i<m;i++)
		{
			_l=bsearch(l,r,i,a[i]);
			_r=bsearch(l,r,i,a[i]+1);
			l=_l,r=_r;
			if (l==r)	break;
		}
		return make_pair(l,r);
	}
	
	int get(int i)	{return rank[i]+1;}
}*S;

void rev(char *s)
{
	int N=strlen(s);
	for (int i=0;i<N/2;i++)	swap(s[i],s[N-i-1]);
}

int n,ng,L,R;
char s[2000000],op[500010];
char sav[12000000];
int nowl[510000],nowr[510000],ans[510000],Cnt;

struct quary
{
	int id,index,x,l,r;
}	q[810000];

bool operator <(quary a,quary b)	{return a.x>b.x;}

void readin()
{
	char *now=sav;
	int lr=0;
	L=R=550000;
	scanf("%d",&ng);
	int sumlen=0;
	for (int i=0;i<ng;i++)
	{
		scanf("%s",op);
		nowl[i]=nowr[i]=-1;
		if (op[0]=='R')	lr^=1;
		if (op[0]=='+')
		{
			if (lr)
			{
				int N=strlen(op+1);
				for (int j=1;j<=N;j++)	s[--L]=op[j];
			}
			else
			{
				int N=strlen(op+1);
				for (int j=1;j<=N;j++)	s[R++]=op[j];
			}
		}
		if (op[0]=='?')
		{
			nowl[i]=L;
			nowr[i]=R;
			if (lr)	rev(op+1);
			int N=strlen(op+1);
			sumlen+=N;
			for (int j=1;j<=N;j++)
			{
				*now=op[j];
				now++;
			}
			now++;
		}
	}
}

void prepare()
{
	char *now=sav;
	readin();
	S=new Suffix_Array(s+L);
	T=new Binary_Indexed_Trees(R-L);
	for (int i=0;i<ng;i++)
	{
		if (nowl[i]>=0)
		{
			pair<int,int> temp=S->find(now);
			q[Cnt*2].l=temp.first;
			q[Cnt*2].r=temp.second;
			q[Cnt*2].index=1;
			q[Cnt*2].x=nowl[i];
			q[Cnt*2].id=Cnt;
			
			q[Cnt*2+1].l=temp.first;
			q[Cnt*2+1].r=temp.second;
			q[Cnt*2+1].index=-1;
			q[Cnt*2+1].x=nowr[i]-strlen(now)+1;
			q[Cnt*2+1].id=Cnt;
			
			Cnt++;
			now+=strlen(now)+1;
		}
	}
	sort(q,q+Cnt*2);
}

void solve()
{
	int temp,ll=R;
	for (int i=0;i<Cnt*2;i++)
	{
		while (ll>q[i].x)
		{
			ll--;
			T->add(S->get(ll-L),1);
		}
		temp=T->ask(q[i].r)-T->ask(q[i].l);
		ans[q[i].id]+=temp*q[i].index;
	}
	for (int i=0;i<Cnt;i++)	printf("%d\n",max(ans[i],0));
}

int main()
{
	freopen("factory.in","r",stdin);
	freopen("factory.out","w",stdout);
	prepare();
	solve();
	return 0;
}

