#include<bits/stdc++.h>
using namespace std;

int isPrime(int n)
{
	if(n==1)
		return 0;
	if(!(n&1))
	{
		if(n==2)
			return 1;
		else
			return 0;
	}
	int lim = (int)(sqrt(n));
	for(int i=3;i<=lim;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
int main()
{
	ofstream fout;
	fout.open("171IT208_IT462_Output_File.txt");
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int res = isPrime(n);
		if(res)
			printf("Prime\n");
		else
			printf("Not prime\n");
	}
	

	return 0;
}