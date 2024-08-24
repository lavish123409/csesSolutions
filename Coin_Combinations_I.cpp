#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int solve(int c[], int n, int x, int dp[])
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
        taken = (taken + solve(c, n, x - c[i], dp)) % mod;
    // cout << ps << "t : " << taken;
    // int notTaken = solve(c, ind-1, n, x);
    // cout << ps << "nt : " << notTaken;
    // ps.pop_back();
    return dp[x] = taken;
}

int solve1(int c[], int ind, int x)
{
    if(x == 0)
        return 1;

    if(ind < 0 || x < 0)
        return 0;
    
    ps.push_back('\t');
    cout << ps << ind << " : " << c[ind] << " = " << x;

    int taken = 0;
    taken = solve1(c, ind, x - c[ind]);
    cout << ps << "t : " << taken;
    int notTaken = solve1(c, ind-1, x);
    cout << ps << "nt : " << notTaken;
    ps.pop_back();
    return taken + notTaken;
}

int main()
{
    int i, j, n, x;
    cin >> n >> x;

    int c[n], dp[x+1];
    for(i=0;i<n;i++)
        cin >> c[i];

    // int dp[x+1];
    // memset(dp, -1, sizeof(dp));
    // cout << solve(c, n, x, dp) << "\n";
    int mod = int(1e9+7);
    dp[0] = 1;
    for(i=1;i<=x;i++)
    {
        dp[i] = 0;
        for(j=0;j<n;j++)
            if(i - c[j] >= 0)
            {
                dp[i] = (dp[i] + dp[i - c[j]]) % mod;
            }
    }

    cout << dp[x] << "\n";

    
    return 0;
}