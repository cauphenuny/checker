#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+5;
const int m=50;
int q,n;
struct bit_2{
	LL m[52];
}a[N],t,ans;
int sum[52][2];
inline bit_2 get(LL x)
{
	bit_2 s;
	memset(s.m,0,sizeof s.m);
	int p=0;
	while(x){
		s.m[++p]=x&1ll;
		x>>=1ll;
	}
	return s;
}
inline bool check(LL locate,LL x)
{//cout<<locate<<" "<<x<<endl;
	if(locate==0){
		if(x>=0ll) return 1;
		else return 0;
	}
	LL sum1=sum[locate][1];
	LL sum0=sum[locate][0];
	bool ok=0;
//	if(sum1<=sum0){
	LL tag=sum0*(1ll<<(locate-1));
	LL tag2=sum1*(1ll<<(locate-1));
	//cout<<"locate= "<<locate<<" "<<tag<<" "<<tag2<<" "<<x<<endl;
	if(sum0<=x/(1ll<<(locate-1))){//printf("--%d\n",locate);
		x-=tag,ok=1,ans.m[locate]=1;
		if(!check(locate-1,x))
			x+=tag,ok=1,ans.m[locate]=0;
		else return 1;
		if(x/(1ll<<(locate-1,x))<sum1) return 0;
		x-=tag2,ok=1,ans.m[locate]=0;
		if(!check(locate-1,x)) return 0; 
	} 
	else{
		if(x/(1ll<<(locate-1))<sum1) return 0;
		x-=tag2,ok=1,ans.m[locate]=0;
		if(!check(locate-1,x)) return 0;
	}
//	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	LL x;
	for(register int i=1;i<=n;++i){
		scanf("%lld",&x);
		a[i]=get(x);
	}
	for(register int i=m;i>=1;--i){
		for(register int j=1;j<=n;++j){
			if(a[j].m[i]) ++sum[i][1];
			else ++sum[i][0];
		}
	}
	//for(register int i=1;i<=n;++i){
	//	for(register int j=m;j>=1;--j) cout<<"locate= "<<j<<" = "<<sum[j][0]<<" "<<sum[j][1]<<endl;puts("");
//	}
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%lld",&x);
		memset(t.m,0,sizeof t.m);
		memset(ans.m,0,sizeof ans.m);
		t=get(x);
		if(!check(m,x)) puts("-1");
		else{
			LL answ=0;
		//	for(register int i=1;i<=m;++i) cout<<ans.m[i];puts("");
			for(register int i=1;i<=m;++i){
				answ+=ans.m[i]*(1ll<<(i-1));
			}
			printf("%lld\n",answ);
		}
	}
	return 0;
 } 
