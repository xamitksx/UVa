#if 1
/* TLE  pure backTracking */
#include <iostream>
#include <string.h>
#define AAA 'A'
#define BBB 'B'
#define AVAIL '@'
using namespace std;
int N,E;
typedef struct {
	int u;
	int v;
	int wt;
	char set;
}_ED;
const int SZ = 26;
int TotalEdgesToSelect;
_ED ed[SZ];
bool nodesA[11];
bool nodesB[11];
int MIN_COST;
bool isSafe(int e ,int slotToFill)
{
	if (slotToFill <= N - 1 && nodesA[ed[e].u] == true && nodesA[ed[e].v] == true)
		return false;
	if (slotToFill >= N  && nodesB[ed[e].u] == true && nodesB[ed[e].v] == true)
		return false;
	return true;
}
void print(int cost)
{
	cout << "Min cost " << cost << endl;
	cout << "A : ";
	for (int i = 1; i <= E; i++)
	{
		if (ed[i].set == AAA)
		{
			cout << ed[i].u << "-" << ed[i].v << "=" << ed[i].wt << " , ";
		}
	}
	cout << "  B : ";
	for (int i = 1; i <= E; i++)
	{
		if (ed[i].set == BBB)
		{
			cout << ed[i].u << " " << ed[i].v << " " << ed[i].wt << " , ";
		}
	}
	cout << endl;
}
void select_edge(int slotToFill, int cur_cost)
{
	if (slotToFill == TotalEdgesToSelect + 1)
	{
		if (MIN_COST > cur_cost)
		{
			MIN_COST = cur_cost;
			print(MIN_COST);
		}
			
		return;
	}
	////try to select first available edge 
	for (int e = 1; e <= E; e++)
	{
		if (ed[e].set != AVAIL) //edge is not available
			continue;
		if (isSafe(e, slotToFill) == true && cur_cost + ed[e].wt < MIN_COST)
		{
			bool stauts_u = false; // I didn't put these so actual stauts was not backed up and 
			bool stauts_v = false; // hence didnt restored properly
			if (slotToFill <= N - 1)
			{
				stauts_u = nodesA[ed[e].u];
				stauts_v = nodesA[ed[e].v];
				nodesA[ed[e].u] = true;
				nodesA[ed[e].v] = true;
				ed[e].set = AAA;
			}
			else if (slotToFill >= N)
			{
				stauts_u = nodesB[ed[e].u];
				stauts_v = nodesB[ed[e].v];
				nodesB[ed[e].u] = true;
				nodesB[ed[e].v] = true;
				ed[e].set = BBB;
			}
			select_edge(slotToFill + 1 , cur_cost + ed[e].wt);
			///backTrack
			ed[e].set = AVAIL;
			if (slotToFill <= N - 1)
			{
				nodesA[ed[e].u] = stauts_u;
				nodesA[ed[e].v] = stauts_v;
			}
			else if (slotToFill >= N)
			{
				nodesB[ed[e].u] = stauts_u;
				nodesB[ed[e].v] = stauts_v;
			}

		}
	}/// for 
	return;

}
int main()
{
	std::ios_base::sync_with_stdio(false);
#if _WIN32
	freopen("10807 - Prim.txt", "r", stdin);
#endif
	while (true)
	{
		cin >> N;
		if (N == 0)
			break;
		cin >> E;
		TotalEdgesToSelect = 2 * (N-1);
		memset(nodesA, false, sizeof(nodesA));
		memset(nodesB, false, sizeof(nodesB));
		MIN_COST = 1 << 30;
		for (int e = 1; e <= E; e++)
		{
			cin >> ed[e].u >> ed[e].v >> ed[e].wt;
			ed[e].set=AVAIL;
		}
		if (E < TotalEdgesToSelect)
			cout << "No way!" << endl; 
		else
		{
			select_edge(1, 0);
			if (MIN_COST == 1 << 30)
				cout << "No way!" << endl;
			else
				cout << MIN_COST << endl;
		}
		

	}
	return 0;
}
#endif
