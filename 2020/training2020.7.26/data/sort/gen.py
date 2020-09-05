from sys import *
from random import *

def work(n,t=True):
	if t:
		p=[]
		for l in range(n):
			p.append(randint(1,l+1))
			for i in range(l):
				if p[i]>=p[l]:
					p[i]+=1
		return p
	c=0
	while 2**c<n:
		c+=1
	c-=1
	g=2**randint(c//2,c)
	l=max(g-7,1)
	r=min(n-1,g*2,l+8)
	m=randint(l,r)+1
	s=[1]*m
	q=n-m
	for i in range(q//2):
		s[randint(0,m-1)]+=1
	q-=q//2
	while q>0:
		e=(q+1)//2
		q-=e
		while e>0:
			x=randint(1,e)
			s[randint(0,m-1)]+=x
			e-=x
	st=[0]*n
	vis=[False]*n
	su=0
	for x in s:
		st[su]+=1
		st[su+x-1]+=2
		su+=x
	res=[0]*n
	for i in range(n):
		candidate=[]
		for j in range(n):
			if vis[j]:
				continue
			if st[j]>=2:
				if (j+1==n or vis[j+1]==True) and (st[j]%2==1 or vis[j-1]==True):
					candidate.append(j)
			elif st[j]==1 or vis[j-1]==True:
				candidate.append(j)
		x=candidate[randint(0,len(candidate)-1)]
		vis[x]=True
		res[i]=x+1
	return res

bat=open('work.bat','w')
bat.write('@echo off\n')
for ts in range(1,21):
	n=0
	f=False
	if ts<=4:
		n=randint(8,10)
	elif ts<=10:
		n=randint(15,20)
	elif ts<=14:
		f=True
		n=randint(2800,3000)
	elif ts<=17:
		n=randint(1500,3000)
	else:
		n=randint(2990,3000)
	w=work(n,f)
	fil=open('sort'+str(ts)+'.in','w')
	fil.write(str(n)+'\n'+' '.join(map(str,w))+'\n')
	fil.close()
	bat.write('sort.exe < sort'+str(ts)+'.in > sort'+str(ts)+'.out\n')
bat.close()