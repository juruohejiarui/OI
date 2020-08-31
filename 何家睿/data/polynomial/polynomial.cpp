#include<cstdio>
#define mo 998244353
using namespace std;
int n,s,len,k,now;
int jc[200005],ny[200005],t[20];
int a[200005],b[200005],ansa[200005],ansb[200005];
int A[524288],B[524288],C[524288],rev[524288],X[524288];
int fail[100005];
inline int read(){
    int ret=0;char c=getchar();
    while((c>'9')||(c<'0'))c=getchar();
    while((c>='0')&&(c<='9'))ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
    return ret;
}
inline int pow(int x,int k){
	int ans=1;
	for(;k;k>>=1,x=1LL*x*x%mo)if(k&1)ans=1LL*ans*x%mo;
	return ans;
}
void NTT(int x[],bool f){
	for(int i=0;i<len;i++)X[i]=x[rev[i]];
	for(int i=0;i<len;i++)x[i]=X[i];
	for(int i=1;i<len;i<<=1){
		int wn=pow(3,(mo-1)/i/2);
		if(!f)wn=pow(wn,mo-2);
		for(int j=0;j<len;j+=2*i){
			for(int k=j,w=1;k<j+i;k++,w=1LL*w*wn%mo){
				int tmp1=x[k],tmp2=1LL*x[k+i]*w%mo;
				x[k]=(tmp1+tmp2)%mo;x[k+i]=(tmp1-tmp2+mo)%mo;
			}
		}
	}
	if(!f){
		int tmp=pow(len,mo-2);
		for(int i=0;i<len;i++)x[i]=1LL*x[i]*tmp%mo;
	}
}
void work(){
	NTT(A,1);
	for(int i=0;i<n;i++)B[i]=a[i+1];
	NTT(B,1);
	for(int i=0;i<len;i++)C[i]=1LL*A[i]*B[i]%mo;
	NTT(C,0);
	for(int i=k+1;i<n;i++)ansa[i-k]=(C[i]-a[i+1]+mo)%mo;
	for(int i=0;i<2*n;i++)B[i]=b[i+1];
	for(int i=2*n;i<len;i++)B[i]=0;
	NTT(B,1);
	for(int i=0;i<len;i++)C[i]=1LL*A[i]*B[i]%mo;
	NTT(C,0);
	for(int i=k+1;i<=n+k;i++)ansb[i-k]=ansb[i-k+n]=(C[i]-b[i+1]+mo)%mo;
}
void pre(){
	jc[0]=1;
	for(int i=1;i<=k+1;i++)jc[i]=1LL*jc[i-1]*i%mo;
	ny[k+1]=pow(jc[k+1],mo-2);
	for(int i=k+1;i;i--)ny[i-1]=1LL*ny[i]*i%mo;
	for(int i=1;i<=k+1;i++){
		A[i]=1LL*ny[k+1-i]*ny[i]%mo*jc[k+1]%mo;
		if(i&1^1)A[i]=(mo-A[i])%mo;
	}
	len=1;s=1;
	while(len<n)len<<=1,s++;len<<=2;s++;
	for(int i=0;i<len;i++){
		rev[i]=i;
		for(int j=0;j<s;j++)t[j]=rev[i]&1,rev[i]>>=1;
		for(int j=0;j<s;j++)rev[i]=(rev[i]<<1)|t[j];
	}
}
int main(){
	freopen("polynomial10.in","r",stdin);
	freopen("polynomial10.out","w",stdout);
	n=read();k=read();
	if(k+1>=n){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=b[i+n]=read();
	pre();work();
	for(int i=2;i<=n-k-1;i++){
		int tmp=fail[i-1];
		while((tmp)&&(ansa[tmp+1]!=ansa[i]))tmp=fail[tmp];
		if(ansa[tmp+1]==ansa[i])fail[i]=tmp+1;
	}
	now=0; 
	for(int i=1;i<=n*2;i++){
		while((ansa[now+1]!=ansb[i])&&(now))now=fail[now];
		if(ansa[now+1]==ansb[i])now++;
		if(now==n-k-1){
			printf("%d",i-(n-k-1));
			return 0;
		}
	}
	puts("-1");
}
