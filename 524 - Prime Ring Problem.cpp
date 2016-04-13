#if 1
#include <iostream>
#include <string.h>
using namespace std;
const int SZ = 17;
const int PIRMETill = 32;
bool isprime[PIRMETill + 1] = { true };
int N;
int op[SZ];
bool taken[SZ] = { false };
void fillPrime(void)
{
	memset(isprime, true, sizeof(isprime));
	for (int i = 2; i*i <= PIRMETill; i++)
	{
		if (isprime[i] == false)
			continue;
		for (int m = 2; m*i <= PIRMETill; m++)
		{
			int mul = m*i;
			if (isprime[mul] == true)
			{
				isprime[mul] = false;
			}
		}
	}
}
bool checkPrimesum(int nu,int index)
{
	int sumPrev = nu + op[index - 1];
	if (isprime[sumPrev] == false)
		return false;
	if (index == N)  // if we are placing last no then prime condition has to be checked with both prev and next(first nu)
	{
		int sumNext = nu + op[1];
		if (isprime[sumNext] == false)
			return false;
	}
	return true;
}
void fill_ring(int index)
{
	if (index == N + 1)
	{
		cout << op[1];
		for (int i = 2; i <= N; i++)
			cout << " " << op[i];
		cout << endl;
		return;
	}
	///try placing all numer on given slot
	for (int i = 1; i <= N; i++)
	{
		if (taken[i] == false && checkPrimesum(i,index)==true)
		{
			taken[i] = true;
			op[index] = i;
			fill_ring(index + 1);
			taken[i] = false;
			op[index] = 0;
		}
	}
	return;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("UVA_524_PrimeRing.txt","r",stdin);
#endif
	//int T;
	//cin >> T;
	int t = 1;
	fillPrime();
	//while (T--)
	while (true)
	{
		cin >> N;
		if (!cin)
			break;
		if (t > 1)
			cout << endl;
		cout << "Case " << t++ << ":" << endl;
		op[1] = 1; // first is always fix 
		taken[1] = true;
		fill_ring(2);
		
	}
	return 0;
}
#endif
