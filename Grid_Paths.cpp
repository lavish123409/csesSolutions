#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

bool isValid(int i, int j, int m, int n)
{
    return (i >= 0 && i < m && j >=0 && j < n);
}

int getNumberOfPaths(vector<vector<char>>& grid, int n, int i, int j, vector<vector<int>>& dp)
{
    if(!isValid(i, j, n, n) || grid[i][j] == '*')
        return 0;

    if(i == 0 && j == 0)
        return 1;

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = getNumberOfPaths(grid, n, i-1, j, dp);
    int left = getNumberOfPaths(grid, n, i, j-1, dp);

    return dp[i][j] = (up + left) % int(1e9 + 7);
}


int main()
{
    int i, j, n, x;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin >> grid[i][j];

    cout << getNumberOfPaths(grid, n, n-1, n-1, dp) << "\n";

    return 0;
}