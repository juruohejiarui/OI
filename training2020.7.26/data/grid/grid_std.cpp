#include <bits/stdc++.h>
using namespace std;

int n,m,a[305][305],px[100010],py[100010],b[305];
string ans; int cnt;
char s[20];

void MR(int x,int k)
{
	while(k<0) k+=m;
	sprintf(s,"1 %d %d\n",x,k),ans+=s,++cnt;
	if (k>0)
		{
			for (int i=0; i<m-k; i++)  b[i+k]=a[x][i];
			for (int i=m-k; i<m; i++)  b[i-m+k]=a[x][i];
		}else
		{
			for (int i=0; i<-k; i++)  b[i+m+k]=a[x][i];
			for (int i=-k; i<m; i++)  b[i+k]=a[x][i];
		}
	for (int i=0; i<m; i++)  a[x][i]=b[i],py[a[x][i]]=i;
}

void MC(int y,int k)
{
	while(k<0) k+=n;
	sprintf(s,"2 %d %d\n",y,k),ans+=s,++cnt;
	if (k>0)
		{
			for (int i=0; i<n-k; i++)  b[i+k]=a[i][y];
			for (int i=n-k; i<n; i++)  b[i-n+k]=a[i][y];
		}else
		{
			for (int i=0; i<-k; i++)  b[i+n+k]=a[i][y];
			for (int i=-k; i<n; i++)  b[i+k]=a[i][y];
		}
	for (int i=0; i<n; i++)  a[i][y]=b[i],px[a[i][y]]=i;
}

void solve(int x,int k)
{
	MC(x,-1);
	for (int i=1; i<k; i+=2)  MR(n-1,-1),MC(x,1),MR(n-1,-1),MC(x,-1);
	MR(n-1,k-1),MC(x,1);
}

void solve2(int x)
{
	MC(x,-1),MR(n-1,-2),MC(x,1),MR(n-1,1),MC(x,-1),MR(n-1,1),MC(x,1);
}

void work()
{
	scanf("%d %d",&n,&m);
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			{
				scanf("%d",&a[i][j]);
				px[a[i][j]]=i,py[a[i][j]]=j;
			}
	for (int i=0,x,y; i<m; i++)
		{
			x=px[i],y=py[i];
			if (x)
				if (y!=i)  MR(x,i-y),MC(i,-x);
				else  MC(i,-x);
			else  if (y!=i)
				{if (i)  MC(y,1),MR(1,i-y),MC(i,-1);  else  MR(0,-y);}
		}
	for (int i=1,x,y; i<n-1; i++)
		for (int j=0; j<m; j++)
			{
				x=px[i*m+j],y=py[i*m+j];
				if (x!=i)
					if (y!=j)  MC(j,x-i),MR(x,j-y),MC(j,i-x);
					else  MR(x,-1),MC(j,x-i),MR(x,1),MC(j,i-x);
				else  if (y!=j)  MR(i,j-y),MC(j,-1),MR(i,y-j),MC(j,1);
			}
	if (py[(n-1)*m])  MR(n-1,-py[(n-1)*m]);
	for (int i=1,x=n-1,y; i<m-2; i++)
		{
			y=py[x*m+i];
			if (y==i)  continue;
			if ((y-i)&1)  solve(i+1,y-i),solve2(i);
			else  solve(i,y-i+1);
		}
	if (a[n-1][m-2]>a[n-1][m-1])
		{
			if (n&1)
				if (m&1)  puts("-1"),exit(0);
				else
					{
						MR(n-1,2),MC(0,-1),MR(n-1,-1),MC(0,1),MR(n-1,1),MC(0,-1),MR(n-1,-2);
						MR(0,1);
						for (int i=n-2; i>1; i-=2)  MC(0,-1),MR(0,-1),MC(0,-1),MR(0,1);
						MC(0,-1),MR(0,-1),MC(0,-2),MR(0,1);
						MC(1,1),MR(0,2);
						for (int i=m-1; i>1; i-=2)  MC(1,-1),MR(0,1),MC(1,1),MR(0,1);
						MC(1,-1);
					}
			else
				{
					MR(n-1,2),MC(0,-1),MR(n-1,-1),MC(0,1),MR(n-1,1),MC(0,-1),MR(n-1,-2);
					MR(0,1);
					for (int i=n-2; i; i-=2)  MC(0,-1),MR(0,-1),MC(0,-1),MR(0,1);
					MC(0,-2),MR(0,-1);
				}
		}
	cout<<cnt<<'\n'<<ans;
}

int main()
{
	work();
	return 0;
}
