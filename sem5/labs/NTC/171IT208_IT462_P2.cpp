#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll square_and_multiply(ll a,ll x,ll n)
{
	ll y=1,nb=0,xcopy=x;
	while(xcopy)
	{
		nb++;
		xcopy=xcopy>>1;
	}
	xcopy=x;
	//printf("nb is %lld\n",nb);
	//ll y=1;
	for(int i=0;i<=nb-1;i++)
	{
		if(xcopy&1)
		{
			y=(a*y)%n;
		}
		xcopy=xcopy>>1;
		a=(a*a)%n;
	}
	return y;
}
int lucas_test(ll n,int flag)
{
	//printf("n is %lld\n",n);
	if(n<=0)
		return 0;//not a positive int
	if(n==1)
		return 1;//1 is neither prime nor composite
	if(!(n&1))
	{
		if(n==2)
			return 5;//2 is a prime
		//Even number is always composite if not equal to 2
		return 3;
	}
	vector <ll> factors;
	ll exponent,q,limit = (ll)(sqrt(n-1));
	for(int i=2;i<=limit;i++)
	{
		if( ((n-1)%i==0) && (lucas_test(i,0)==5)) //finding prime factors of (n-1)
		{
			factors.push_back(i);
		}
	}

	//if a number has no prime factors, it is a prime itself
	if(factors.size()==0)
	{
		return 5;
	}

	if(flag)
	{
		//outfile<<"Prime factors of "<<n<<" are :"<<end;
		printf("Prime factors of %lld are : \n",(n-1));
		for(int i=0;i<factors.size();i++)
		{
			//outfile<<factors[i]<<" ";
			printf("%lld ",factors[i]);
		}
		//outfile<<endl;
		printf("\n");
	}

	srand(time(NULL));
	for(int i=2;i<=(n-1);i++)
	{
		ll a = 2+rand()%(n-2);
		if(square_and_multiply(a,n-1,n)!=1)
			return 4;//Composite number
		int flag2=1;
		for(int j=0;j<factors.size();j++)
		{
			q = factors[j];
			exponent = (ll)((n-1)/q);
			if(square_and_multiply(a,exponent,n) == 1)
			{
				flag=0;
				//return 4;
			}
		}
		if(flag)
			return 5;
	}
	return 5;
}


int main()
{
	ofstream outfile;
	outfile.open("171IT208_IT462_Output_File.txt", ios::out | ios::trunc );
	ll n,t;
	printf("Enter number of testcases\n");
	scanf("%lld",&t);
	while(t--)
	{
		printf("\n\n");
		printf("Enter number to test\n");
		scanf("%lld",&n);
		int result = lucas_test(n,1);
		if(result==0)
		{
			outfile<<n<<" is not a positive number"<<endl;
			printf("%lld is not a positive integer\n",n);
		}
		else if(result==1)
		{
			outfile<<n<<" is neither prime nor composite"<<endl;
			printf("%lld is neither prime nor composite\n",n);
		}
		else if(result==3)
		{
			outfile<<n<<" is an even number"<<endl;
			printf("%lld is an even number\n",n);
		}
		else if(result==4)
		{
			outfile<<n<<" is a composite number"<<endl;
			printf("%lld is a composite number\n",n);
		}
		else
		{
			outfile<<n<<" is a prime number"<<endl;
			printf("%lld is a prime number\n",n);
		}

	}
	//printf("%d\n",lucas_test(13));
	outfile.close();
	return 0;
}