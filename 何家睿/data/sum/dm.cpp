#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<ctime>
#define N 1000000
#define M 10000000
using namespace std;
inline int Rand(){return (rand()<<16)|rand();}
int main(){
	freopen("sum10.in","w",stdout);
	srand(time(0));
	printf("%d %d %d %d %d %d\n",N,M,Rand()%998244353,Rand()%998244353,3,1);
	
	for(int i=1;i<=N/2;i++)printf("%d ",Rand()%N+1);
	for(int i=1;i<=N/2;i++)printf("%d ",i*2);
}
