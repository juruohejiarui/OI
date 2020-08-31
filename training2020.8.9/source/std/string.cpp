#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef long double ld; 
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

const int MOD = 1e9 + 7;

struct NumberTheory
{
	vector<ll> primes;
	vector<bool> prime;
	vector<ll> totient;
	vector<ll> sumdiv;
	vector<ll> bigdiv;
	void Sieve(ll n)
	{
		prime.assign(n+1, 1);
		prime[1] = false;
		for(ll i = 2; i <= n; i++)
		{
			if(prime[i])
			{
				primes.pb(i);
				for(ll j = i*2; j <= n; j += i)
				{
					prime[j] = false;
				}
			}
		}
	}
	
	ll phi(ll x)
	{
		map<ll,ll> pf;
		ll num = 1; ll num2 = x;
		for(ll i = 0; primes[i]*primes[i] <= x; i++)
		{
			if(x%primes[i]==0)
			{
				num2/=primes[i];
				num*=(primes[i]-1);
			}
			while(x%primes[i]==0)
			{
				x/=primes[i];
				pf[primes[i]]++;
			}
		}
		if(x>1)
		{
			pf[x]++; num2/=x; num*=(x-1);
		}
		x = 1;
		num*=num2;
		return num;
	}
	
	bool isprime(ll x)
	{
		if(x==1) return false;
		for(ll i = 0; primes[i]*primes[i] <= x; i++)
		{
			if(x%primes[i]==0) return false;
		}
		return true;
	}

	void SievePhi(ll n)
	{
		totient.resize(n+1);
		for (int i = 1; i <= n; ++i) totient[i] = i;
		for (int i = 2; i <= n; ++i)
		{
			if (totient[i] == i)
			{
				for (int j = i; j <= n; j += i)
				{
					totient[j] -= totient[j] / i;
				}
			}
		}
	}
	
	void SieveSumDiv(ll n)
	{
		sumdiv.resize(n+1);
		for(int i = 1; i <= n; ++i)
		{
			for(int j = i; j <= n; j += i)
			{
				sumdiv[j] += i;
			}
		}
	}
	
	ll getPhi(ll n)
	{
		return totient[n];
	}
	
	ll getSumDiv(ll n)
	{
		return sumdiv[n];
	}
	
	ll modpow(ll a, ll b, ll mod)
	{
		ll r = 1;
		if(b < 0) b += mod*100000LL;
		while(b)
		{
			if(b&1) r = (r*a)%mod;
			a = (a*a)%mod;
			b>>=1;
		}
		return r;
	}
	
	ll inv(ll a, ll mod)
	{
		return modpow(a, mod - 2, mod);
	}
	
	ll invgeneral(ll a, ll mod)
	{
		ll ph = phi(mod);
		ph--;
		return modpow(a, ph, mod);
	}
	
	void getpf(vector<ii>& pf, ll n)
	{
		for(ll i = 0; primes[i]*primes[i] <= n; i++)
		{
			int cnt = 0;
			while(n%primes[i]==0)
			{
				n/=primes[i]; cnt++;
			}
			if(cnt>0) pf.pb(ii(primes[i], cnt));
		}
		if(n>1)
		{
			pf.pb(ii(n, 1));
		}
	}

	//ll op;
	void getDiv(vector<ll>& div, vector<ii>& pf, ll n, int i)
	{
		//op++;
		ll x, k;
		if(i >= pf.size()) return ;
		x = n;
		for(k = 0; k <= pf[i].se; k++)
		{
			if(i==int(pf.size())-1) div.pb(x);
			getDiv(div, pf, x, i + 1);
			x *= pf[i].fi;
		}
	}
};

NumberTheory nt;

ll modpow(ll a, ll b)
{
	ll r = 1;
	while(b)
	{
		if(b&1) r=(r*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return r;
}

ll inv(ll a)
{
	return modpow(a,MOD-2);
}

ll n;
ll cnt[300001];
ll mob[300001];

ll mobius(ll x)
{
	int cc = 0;
	for(int i=0;nt.primes[i]*nt.primes[i]<=x;i++)
	{
		int z=0;
		while(x%nt.primes[i]==0)
		{
			z++;
			x/=nt.primes[i];
		}
		if(z>=2) return 0;
		if(z>0) cc++;
	}
	if(x>1) cc++;
	if(cc&1) return -1;
	else return 1;
}

ll solve(ll x, ll y)
{
	if(x==0&&y==0)
	{
		for(int i=1;i<=n;i++)
		{
			cnt[i]=ll(n/i)*ll(n/i);
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=2*i;j<=n;j+=i)
			{
				cnt[i]+=mob[j/i]*cnt[j];
			}
		}	
		ll ans = 0;
		ll cur = 2;
		for(int i=1;i<=n;i++)
		{
			cnt[i]%=MOD;
			if(cnt[i]<0) cnt[i]+=MOD;
			//cerr<<i<<' '<<cnt[i]<<'\n';
			ans=(ans+(cur*cnt[i])%MOD)%MOD;
			if(ans<0) ans+=MOD;
			cur=(cur*2)%MOD;
			if(cur<0) cur+=MOD;
		}
		return ans;
	}
	else if(x>=0&&y>=0)
	{
		return 0;
	}
	else if(x<=0&&y<=0)
	{
		return 0;
	}
	else
	{
		x=abs(x); y=abs(y);
		ll g = __gcd(x,y);
		x/=g; y/=g;
		ll k = n/max(x,y);
		ll ans = modpow(2,k+1)+MOD-2;
		while(ans>=MOD) ans-=MOD;
		return ans;
	}
}

ll fact[600001];
ll ifact[600001];
ll inverse[600001];

ll choose(ll n, ll r)
{
	if(r==0) return 1;
	ll ans = fact[n];
	ans=(ans*ifact[r])%MOD;
	ans=(ans*ifact[n-r])%MOD;
	if(ans<0) ans+=MOD;
	return ans;
}

int main()
{
  freopen("string.in","r",stdin);
  freopen("string.out","w",stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	string s, t;
	cin>>s>>t;
	cin>>n;
	fact[0]=1; ifact[0]=1;
	for(int i=1;i<=600000;i++)
	{
		fact[i]=(fact[i-1]*i)%MOD;
		if(fact[i]<0) fact[i]+=MOD;
		ifact[i]=inv(fact[i]);
		inverse[i]=inv(i);
	}
	nt.Sieve(300001);
	for(int i=2;i<=n;i++)
	{
		mob[i]=mobius(i);
	}
	ll sa, sb, sc; //sa = # of As in s, sb = # of Bs in s, sc = # of ?s in s
	ll ta, tb, tc;
	sa=sb=sc=ta=tb=tc=0;
	ll same = 1; //number of ways to fill in ?s such that |S| = |T|
	if(s.length()!=t.length()) same=0;
	else
	{
		for(int i=0;i<s.length();i++)
		{
			if(s[i]=='?'&&t[i]=='?') same=(same*2)%MOD;
			else if(s[i]=='?'||t[i]=='?')
			{
				
			}
			else if(s[i]==t[i])
			{
				
			}
			else
			{
				same=0;
			}
		}
	}
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='A') sa++;
		else if(s[i]=='B') sb++;
		else sc++;
	}
	for(int i=0;i<t.length();i++)
	{
		if(t[i]=='A') ta++;
		else if(t[i]=='B') tb++;
		else tc++;
	}
	ll ans = 0;
	ll c = 1;
	int cntt=0;
	for(ll i = sa - ta - tc; i <= sa - ta + sc; i++)
	{
		if(i==0)
		{
			ll cc = (c-same)%MOD;
			if(cc<0) cc+=MOD;
			ans=(ans+(cc*solve(i,sa+sb+sc-ta-tb-tc-i))%MOD)%MOD;
			ll tmp = modpow(2,n+1)+MOD-2;
			while(tmp>=MOD) tmp-=MOD;
			tmp=(tmp*tmp)%MOD;
			ans=(ans+(same*tmp)%MOD)%MOD;
		}
		else
		{
			ans=(ans+(c*solve(i,sa+sb+sc-ta-tb-tc-i))%MOD)%MOD;
		}
		if(ans<0) ans+=MOD;
		c=(c*inverse[cntt+1])%MOD;
		c=(c*(sc+tc-cntt))%MOD;
		if(c<0) c+=MOD;
		cntt++;
	}
	cout<<ans<<'\n';
}
