#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	srand(time(0));
	int n=1e5;
	cout<<n<<endl;
	for(register int i=1;i<=n;++i){
		for(int i=1;i<=2;++i) cout<<rand()%100+900;cout<<rand()%10+1;
		//cout << rand() % 32;
		putchar(' ');
	}
	int m=1e5;
	cout << endl << m << endl;
	for(register int i=1;i<=m;++i){
		for(register int j=1;j<=4;++j) cout<<rand()%100+900;puts("");
		//cout << rand() % 4096 << endl;;
	}
	return 0;
}
