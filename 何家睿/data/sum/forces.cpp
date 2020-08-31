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
inline long long calc(int l,int r){
	int x=0;long long ans=0;
	for(int i=l;i<=r;i++){
		x=max(x,a[i]);
		ans+=1LL*(i-l+1)*x;
	}
	return ans;
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&m,&seed1,&seed2,&d,&p);
	for(int i=1;i<=n;i++)a[i]=read();
	while(m--){
		printf("%d %d\n",seed1,seed2); 
		int l=(seed1+p*lastans)%n+1,r=(seed2+p*lastans)%n+1;
		if(l>r)swap(l,r);
		lastans=calc(l,r);

		seed1=1LL*seed1*d%998244353,seed2=1LL*seed2*d%998244353;
		printf("%d %d %lld\n",l,r,calc(l,r));
	}
}
