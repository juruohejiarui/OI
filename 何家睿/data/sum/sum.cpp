#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
    int ret=0;char c=getchar();
    while((c>'9')||(c<'0'))c=getchar();
    while((c>='0')&&(c<='9'))ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
    return ret;
}
int n,m,seed1,seed2,d,p;
long long lastans;
int a[1000005];
int st[20][1000005],size[1000005];
long long S[1000005],s[1000005];
int stack[1000005],rt[1000005];
void pre(){
	size[1]=0;
	for(int i=2;i<=n;i++)
		if(i==(1<<(size[i-1]+1)))size[i]=size[i-1]+1;
		else size[i]=size[i-1];
	for(int i=1;i<=n;i++)st[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			if(a[st[i-1][j]]>a[st[i-1][j+(1<<(i-1))]])st[i][j]=st[i-1][j];
			else st[i][j]=st[i-1][j+(1<<(i-1))];
	int top=0;
	for(int i=1;i<=n;i++){
		while((top)&&(a[stack[top]]<a[i]))
			rt[stack[top--]]=i;
		stack[++top]=i;
	}
	while(top)rt[stack[top--]]=n+1; 
	for(int i=n;i;i--){
		s[i]=s[rt[i]]+1LL*(rt[i]-i)*a[i];
		S[i]=S[rt[i]]+1LL*(rt[i]-i)*(rt[i]-1+i)/2*a[i];
	}
}
inline int rmq(int l,int r){
	int s=size[r-l+1];
	if(a[st[s][l]]>a[st[s][r-(1<<s)+1]])return st[s][l];
	else return st[s][r-(1<<s)+1];
}
inline long long calc(int l,int r){
	long long ans=0;
	int p=rmq(l,r);
	ans+=S[l]-S[p]+1LL*(r-p+1)*(r+p)/2*a[p];
	ans-=(l-1)*(s[l]-s[p]+1LL*(r-p+1)*a[p]);
	return ans;
}
int main(){
	freopen("sum10.in","r",stdin);
	freopen("sum10.out","w",stdout);
	scanf("%d%d%d%d%d%d",&n,&m,&seed1,&seed2,&d,&p);
	for(int i=1;i<=n;i++)a[i]=read();
	pre();
	long long ans=0;
	while(m--){
		int l=(seed1+p*lastans)%n+1,r=(seed2+p*lastans)%n+1;
		if(l>r)swap(l,r);
		lastans=calc(l,r);
		seed1=1LL*seed1*d%998244353,seed2=1LL*seed2*d%998244353;
		ans^=lastans;
	}
	printf("%lld",ans); 
}
