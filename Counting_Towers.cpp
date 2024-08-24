#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int towerWays(int n, bool oc, vector<vector<int>>& dp) {
    if(n == 1) {
        return 1;
    }

    if(dp[n][oc] != -1) {
        return dp[n][oc];
    }

    int ans = 0, mod=int(1e9+7);
    if(oc) {
        ans = (1ll * towerWays(n-1, 0, dp)
            + 4ll * towerWays(n-1, 1, dp)) % mod;
    }
    else {
        ans = (2ll * towerWays(n-1, 0, dp)
            + 1ll * towerWays(n-1, 1, dp)) % mod;
    }

    return dp[n][oc] = ans;
}

int main()
{
    int t;
    cin >> t;

    int n=int(1e6);
    vector<vector<int>> dp(n+1, vector<int>(2));
    dp[1][0] = 1;
    dp[1][1] = 1;

    int i, j, mod=int(1e9+7);
    for(i=2;i<=n;i++) {
        dp[i][0] = (2ll * dp[i-1][0]
                    + 1ll * dp[i-1][1]) % mod;

        dp[i][1] = (1ll * dp[i-1][0]
                    + 4ll * dp[i-1][1]) % mod;
    }


    while(t--) {
        int n;
        cin >> n;

        cout << (1ll * dp[n][0] + dp[n][1]) % mod << "\n";
        // cout << (1ll * towerWays(n, 0, dp) + towerWays(n, 1, dp)) % int(1e9+7) << "\n";
    }

    return 0;
}