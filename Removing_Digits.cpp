#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int solve(int n, int dp[])
{
    if(n == 0)
        return 0;

    if(dp[n] != -1)
        return dp[n];

    // ps.push_back('\t');
    int i, nd=log10(n) + 1, pw=1;
    int ans=  INT_MAX;
    // cout << ps << n << " -> ";
    for(i=0;i<nd;i++)
    {
        int ld = (n / pw) % 10;
        pw *= 10;
        // cout << ps << ld << " : ";
        if(ld == 0)
            continue;
        int cans = 1 + solve(n - ld, dp);
        // cout << ps << cans;
        ans = min(ans, cans);
    }
    // cout << ps << ans;

    // ps.pop_back();
    return dp[n] = ans;
}


int main()
{
    int i, j, n, x;
    cin >> n;

    int dp[n+1];
    memset(dp, -1, sizeof(dp));
    cout << solve(n, dp) << "\n";

    return 0;
}