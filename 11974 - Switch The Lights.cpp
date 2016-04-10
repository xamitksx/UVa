/*Take initial state of BULBS is all ON (1's) i.e 111
   Need to reach all OFF state i.e 000 by available switches : switch 1 and/or 2 
Keep applying all switches on initial State and RUN BFS on the STATES.....
 switch 1 --101  
 applying Switch 1 on initial STATE (111)  111 XOR 101 = 010
 switch 2 --110 
 applying Switch 2 on initial STATE (111)  111 XOR 110 = 001

 111 ----^101 ---> 010 ----^110---->100 ---^110------>010----^110-->100 
     |            |--- ^101--->111   |----^101-->001
	 |
	 |--2-->001--- 1---> 100
	         |---- 2 ---> 111
101--5
110 -6
 */
#if 1
#include<iostream>
#include<string.h>
using namespace std;
int B, S;
int Initial_state = 1; //should be all ones
int Final_state = 0; // final state
int switches[101];
#define TWO_POW_15 32768
bool done[TWO_POW_15 + 1] = { false };
typedef struct {
	int state;
	int lev;
}_PT;
_PT que[TWO_POW_15 + 1];
int front = 0, rear = 0;
int bsf()
{
	_PT start;
	start.state = Initial_state;
	start.lev = 0;
	done[start.state] = true;
	que[rear++] = start;
	while (front!=rear)
	{//pop
		_PT u = que[front++];
		///apply all switches to current state
		for (int i = 1; i <= S; i++)
		{
			_PT v;
			v.state = u.state ^switches[i] ;
			v.lev = u.lev + 1;
			if (v.state ==  Final_state )
			{
				return v.lev;
			}
			else if (done[v.state] == false)
			{
				done[v.state] = true;
				que[rear++] = v;
			}
		}
	}
	return -1;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("UVA_11974 - Switch The Lights.txt", "r", stdin);
#endif
	int T;
	cin >> T;
	int t = 1;
	while (T--)
	{
		cin >> B >> S;
		Initial_state = ( 1 << B ) - 1; // set B 1's in int variable Initial_state
		int sw;
		for (int i = 1; i <= S; i++)
		{
			int _switch = 0;
			for (int j = 1; j <= B; j++)
			{
				cin >> sw;
				_switch = (_switch << 1) + sw;
			}
			switches[i] = _switch; //set all bits of switch in ith switch
		}
		int result = bsf();
		if(result==-1)
			cout << "Case " << t++ << ": " << "IMPOSSIBLE" << endl;
		else
			cout << "Case " << t++ << ": " << result << endl;
		////reset
		front = 0, rear = 0;
		memset(done,false,sizeof(done));
	}

	return 0;
}
#endif
