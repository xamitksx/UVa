#if 1
/*First I used basic permute technique. which resulted in TLE.
problem was solving same problem again . 
Used Top Down DP (recursion with Memoization) */
////  ALL TC passed fast enough
#include <iostream>
#include <cstring>//
//#define DEBUG
using namespace std;
int TotalLen;
int N;
int cutApplied;
const int SZ = 52;
int mark[SZ];
#ifdef DEBUG
int cst[SZ];
int seq[SZ];
#endif
bool taken[SZ];
int dp[SZ][SZ];
// returns Min cost of cutting LOG by provided No of cuts (cutForthisLog) for Log of length lengthOflog . 
// where leftIndex,rightIndex are boundry indexes of given log
int cut(int leftIndex, int  rightIndex, int cutForthisLog, int lengthOflog)
{
	if (cutForthisLog == 0)
	{
		return 0;
	}
	if (cutForthisLog == 1)
	{
		return lengthOflog; /// length is equal to cost
	}
	if (dp[leftIndex][rightIndex] > 0)
		return dp[leftIndex][rightIndex];
	/// try all available cuts one by one 
	int minCostforthisSegment = 1 << ((sizeof(int) * 8) - 2);
	for (int i = leftIndex + 1; i < rightIndex; i++)
	{
		if (taken[i] == false)
		{
			taken[i] = true;
			cutApplied++;
			int lengthOflogLeft = mark[i] - mark[leftIndex];
			int lengthOflogRight = mark[rightIndex] - mark[i];
			int cutleft = 0;
			for (int k = i - 1; k > leftIndex; k--)
			{
				if (taken[k] == false)
					cutleft++;
				else
					break;
			}
			int cutright = cutForthisLog - cutleft - 1;
#ifdef DEBUG
			cst[i] = lengthOflog;  // DEBUG
			seq[cutApplied - 1] = mark[i];  // DEBUG
#endif
			int costL = cut(leftIndex, i, cutleft, lengthOflogLeft);
			int costR = cut(i, rightIndex, cutright, lengthOflogRight);
			int cur_cost = lengthOflog + costL + costR;
			if (minCostforthisSegment >  cur_cost)
				minCostforthisSegment = cur_cost;
#ifdef DEBUG
			cst[i] = 0;  // DEBUG
			seq[cutApplied - 1] = 0;  // DEBUG
#endif
			taken[i] = false;//BT
			cutApplied--; //BT
		}
	}
	//// optimization;
	dp[leftIndex][rightIndex] = minCostforthisSegment;
	return minCostforthisSegment;
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifdef _WIN32
	freopen("UVA_10003 - Cutting Sticks.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	while (1)
	{
		cutApplied = 0;
		cin >> TotalLen;
		if (TotalLen == 0)
			break;
		cin >> N;
		/// fill border no cut will be applied on these
		mark[0] = 0; // start from 0 
		mark[N + 1] = TotalLen; // end at LEN 
		taken[0] = taken[N + 1] = false;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= N; i++)
		{
			cin >> mark[i];
			taken[i] = false;
#ifdef DEBUG
			cst[i] = 0;
			seq[i];
#endif
		}
		int cost = cut(0, N + 1, N, TotalLen);
		cout << "The minimum cutting is "<< cost<<"." << endl;
	}
	return 0;
}

#endif
#if 0
/// basic permute
/// initially i tried this but it is not using DP and results in TLE.
#include <iostream>
#include <string>
using namespace std;
const int SZ = 1001;

int id = 1;
int TotalLen;
int N;
int mark[SZ];
int cost[SZ];
bool taken[SZ];
int output[SZ];

int min_cost = 1 << ((sizeof(int) * 8) - 2);
int cur_cost = 0;
int getsizeofLog(int cut_pos, int index)
{
	int left = index - 1;
	while (left > 0 && taken[left] == false)
	{
		left--;
	}
	int right = index + 1;
	while (right < N + 1 && taken[right] == false)
	{
		right++;
	}

	return mark[right] - mark[left];
}
void recur(int pos)
{
	if (pos == N + 1)
	{
		cout << id++ << " ";
		for (int i = 1; i <= N; i++)
			cout << output[i];
		cout << endl;
		if (cur_cost < min_cost)
			min_cost = cur_cost;
		return;
	}
	for (int i = 1; i <= N; i++)
	{
		if (taken[i] == false)
		{
			int lengthOfLog = getsizeofLog(mark[i], i);
			cur_cost = cur_cost + lengthOfLog;
			cost[pos] = lengthOfLog;  // debug
			output[pos] = mark[i];  // debug
			taken[i] = true;
			recur(pos + 1);
			taken[i] = false; // backtrack
			cur_cost = cur_cost - lengthOfLog; // backtrack
			cost[pos] = 0;      // debug
			output[pos] = '@';  // debug
		}
	}
	return;
}
int main()
{
#ifdef _WIN32
	freopen("UVA_10003 - Cutting Sticks.txt", "r", stdin);
#endif
	while (1)
	{

		cur_cost = 0;
		min_cost = 1 << ((sizeof(int) * 8) - 2);
		cin >> TotalLen;
		if (TotalLen == 0)
			break;
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			cin >> mark[i];
			taken[i] = false;
			cost[i] = 0;

		}
		mark[0] = 0;
		mark[N + 1] = TotalLen;
		taken[N + 1] = false;
		taken[0] = 0;
		recur(1);
		cout << min_cost << endl;
	}
	return 0;
}
#endif 
