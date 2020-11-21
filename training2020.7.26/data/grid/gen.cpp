#include <bits/stdc++.h>
using namespace std;
int cas;
void work(int n,int m){
	++cas;
	string z="grid"+to_string(cas);
	freopen((z+".in").c_str(),"w",stdout);
	vector<int> p(n*m);
	for(int i=0;i<p.size();++i) p[i]=i;
	random_shuffle(p.begin(),p.end());
	if(cas>=20&&n%2==1&&m%2==1){
		vector<vector<int>> a(n,vector<int>(m));
		for(int i=0;i<n;++i) for(int j=0;j<m;++j) a[i][j]=i*m+j;
		for(int t=1;t<=200000;++t){
			int r=rand()%n;
			int c=rand()%m;
			if(rand()&1){
				vector<int> g(m);
				for(int i=0;i<m;++i) g[(i+c)%m]=a[r][i];
				for(int i=0;i<m;++i) a[r][i]=g[i];
			}else{
				vector<int> g(n);
				for(int i=0;i<n;++i) g[(i+r)%n]=a[i][c];
				for(int i=0;i<n;++i) a[i][c]=g[i];
			}
		}
		for(int i=0;i<n;++i) for(int j=0;j<m;++j) p[i*m+j]=a[i][j];
	}
	cout<<n<<' '<<m<<'\n';
	for(int i=0;i<n;++i) for(int j=0;j<m;++j) cout<<p[i*m+j]<<" \n"[j+1==m];
	fclose(stdout);
	system(("grid.exe <"+z+".in >"+z+".out").c_str());
}
int rnd(int l,int r){ return rand()%(r-l+1)+l; }
int main(){
	srand(time(nullptr)^size_t(new char));
	for(int t=1;t<=5;++t) work(rnd(2,3),rnd(2,3));
	for(int t=6;t<=15;++t) work(rnd(4,5),rnd(4,5));
	for(int t=16;t<=25;++t) work(rnd(7,8),rnd(7,8));
	for(int t=26;t<=40;++t) work(rnd(9,10),rnd(9,10));
	for(int t=41;t<=50;++t) work(rnd(17,20),rnd(17,20));
	for(int t=51;t<=55;++t) work(2,rnd(95,100));
	for(int t=56;t<=65;++t) work(3,rnd(95,100));
	for(int t=66;t<=80;++t) work(rnd(4,5),rnd(95,100));
	for(int t=81;t<=100;++t) work(rnd(96,100),rnd(96,100));
}