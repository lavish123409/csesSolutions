#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int solve1(int c[], int n, int x, int dp[])
{
    if(x == 0)
        return 1;

    if(x < 0)
        return 0;

    if(dp[x] != -1)
        return dp[x];
    
    // ps.push_back('\t');
    // cout << ps << x;

    int taken = 0, mod = int(1e9+7);
    for(int i=0;i<n;i++)
        taken = (taken + solve1(c, n, x - c[i], dp)) % mod;
    // cout << ps << "t : " << taken;
    // int notTaken = solve(c, ind-1, n, x);
    // cout << ps << "nt : " << notTaken;
    // ps.pop_back();
    return dp[x] = taken;
}

int solve(int c[], int ind, int x, vector<vector<int>>& dp)
{
    if(x == 0)
        return 1;

    if(ind < 0 || x < 0)
        return 0;

    if(dp[ind][x] != -1)
        return dp[ind][x];
    
    // ps.push_back('\t');
    // cout << ps << ind << " : " << c[ind] << " = " << x;

    // int taken = 0;
    int taken = solve(c, ind, x - c[ind], dp);
    // cout << ps << "t : " << taken;
    int notTaken = solve(c, ind-1, x, dp);
    // cout << ps << "nt : " << notTaken;
    // ps.pop_back();
    return dp[ind][x] = (taken + notTaken) % int(1e9+7);
}

int main()
{
    int i, j, n, x;
    cin >> n >> x;

    int c[n];
    for(i=0;i<n;i++)
        cin >> c[i];

    // int dp[x+1];
    // memset(dp, -1, sizeof(dp));
    vector<vector<int>> dp(n, vector<int>(x+1));
    // cout << solve(c, n-1, x, dp) << "\n";
    int mod = int(1e9+7);
    // dp[0] = 1;

    // for(i=0;i<n;i++)
    //     dp[i][0] = 0;

    // for(i=1;i<=x;i++)
    // {
    //     // dp[i] = 0;
    //     for(j=0;j<n;j++)
    //         if(i - c[j] >= 0)
    //         {
    //             dp[i][j] = (dp[i][i - c[j]] + dp[x][j]) % mod;
    //         }
    // }
    for(i=0;i<n;i++)
    {
        for(j=0;j<=x;j++)
        {
            if(j == 0)
                dp[i][j] = 1;
            else
            {
                if(j - c[i] >= 0)
                    dp[i][j] = dp[i][j - c[i]];
                if(i > 0)
                    dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
            }
        }
    }

    // for(i=0;i<n;i++)
    // {
    //     for(j=0;j<=x;j++)
    //         cout << dp[i][j] << " ";
    //     cout << "\n";
    // }

    cout << dp[n-1][x] << "\n";

    
    return 0;
}