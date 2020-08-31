#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<ctime>
#define N 100000
#define M 5000
using namespace std;
int m;
int a[N+5],s[N+5];
int f(int x){
	int ans=0;
	for(int i=0;i<=m;i++)ans=(1LL*ans*x+a[i])%998244353;
	return ans;
}
inline int Rand(){return (rand()<<16)|rand();}
int main(){
	freopen("polynomial10.in","w",stdout);
	srand(time(0));
	int n=N;
	m=rand()%M;
	for(int i=0;i<=m;i++)a[i]=Rand()%998244353;
	for(int i=0;i<n;i++)s[i]=f(i);
	printf("%d %d\n",n,m+rand()%(m+1));
	for(int i=0;i<n;i++)printf("%d ",s[i]);
	int d=Rand()%998244353,D=rand()%N;
	puts("");
	for(int i=0;i<n;i++)printf("%d ",(s[(i+D)%n]+d)%998244353);
}
