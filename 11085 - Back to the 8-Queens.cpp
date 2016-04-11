#if 1
#include<iostream>
#include<string.h>
using namespace std;
int const SZ = 9;
int mat[SZ][SZ];
int result[93][SZ][SZ];
int N = 8;
int cnt = 1;
bool isSafe(int r, int c)
{
	/// till top in same col
	for (int i = r; i >= 1; i--)
		if (mat[i][c] == 1)
			return false;
	///till top in diagnol cols 
	for (int i = r - 1, k = 1; i >= 1; i--, k++)
	{
		int left = c - k;
		int right = c + k;
		if (left >= 1 && left <= N && mat[i][left] == 1)
			return false;
		if (right >= 1 && right <= N && mat[i][right] == 1)
			return false;
	}
	return true;
}
void placeQueen(int row)
{
	if (row == 9)
	{
		///print matrix
		//cout << cnt << ":" << endl;
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				//cout << mat[i][j];
				result[cnt][i][j] = mat[i][j];;
			}
			//cout << endl;
		}
		cnt++;
		//cout << endl;
		return;
	}
	///for given row try all colums
	for (int c = 1; c <= 8; c++)
	{
		if (isSafe(row, c) == true)
		{
			mat[row][c] = 1;
			placeQueen(row + 1);
			mat[row][c] = 0; //BT
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("UVA_11085 - Back to the 8-Queens.txt", "r", stdin);
	freopen("Text.txt", "w", stdout);
#endif

	memset(mat, 0, sizeof(mat));
	placeQueen(1);

	int t = 1;
	int a;
	while (cin >> a)
	{
		memset(mat, 0, sizeof(mat));
		mat[1][a] = 1;
		for (int i = 2; i <= 8; i++)
		 {
			int b;
			cin >>b;
			mat[i][b] = 1;
		}
 	 int min = 1 << 30;
	 //match matrix with all results
	 for (int k = 1; k <= 92; k++)
	 {
	 	int unmatch = 0;
	 	for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				if (result[k][i][j] != mat[i][j])
				{
					unmatch++;
					break;
				}
			}
		}////
		if (min > unmatch)
			min = unmatch;
	 }
	 cout << "Case " << t++ << ": " << min << endl;
    }
	return 0;
}
#endif
#if 0
///simple N queen
#include<iostream>
#include<string.h>
using namespace std;
int const SZ = 9;
int mat[SZ][SZ];
int N = 8;
int cnt = 1;
bool isSafe(int r, int c)
{
	/// till top in same col
	for (int i = r; i >= 1; i--)
		if (mat[i][c] == 1)
			return false;
	////////
	///till top in diagnol cols 
	for (int i = r-1,k=1; i >= 1; i--,k++)
	{
		int left = c - k;
		int right = c + k;
		if(left>=1 && left<=N && mat[i][left] == 1)
			return false;
		if (right >= 1 && right <= N && mat[i][right] == 1)
			return false;			
	}
	return true;
}
void placeQueen(int row)
{
	if (row == 9)
	{
		 ///print matrix
		cout << cnt++ << ":" << endl;
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
				cout << mat[i][j];
			cout << endl;
		}
		cout << endl;
		return;
	}
	///for given row try all colums
	for (int c = 1; c <= 8; c++)
	{
		if (isSafe(row, c) == true)
		{
			mat[row][c] = 1;
			placeQueen(row + 1);
			mat[row][c] = 0; //BT
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	memset(mat, 0, sizeof(mat));
	placeQueen(1);
	return 0;
}
#endif
