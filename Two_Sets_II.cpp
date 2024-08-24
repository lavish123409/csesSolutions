#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 7
/*
    if 1 + 2 + ... + n = n * (n+1) / 2 = sum

    if sum is odd
      print 0
    
    recursion to build sum / 2 from elements till n

    recurse(n, sum):
      takeWays = recurse(n-1, sum - n)
      notTakeWays = recurse(n-1, sum)

      return takeWays + notTakeWays
*/

int solve(int n, int sum, vector<vector<int>>& dp) {
    if(sum == 0) {
        return 1;
    }

    if(n <= 0 || sum < 0) {
        return 0;
    }

    if(dp[n][sum] != -1) {
        return dp[n][sum];
    }

    // ps.push_back('\t');
    // cout << ps << n << " , " << sum;

    int take = solve(n-1, sum - n, dp);
    // cout << ps << "tk: " << take;
    int notTake = solve(n-1, sum, dp);
    // cout << ps << "ntk: " << notTake;
    dp[n][sum] = (1ll * take + notTake) % int(1e9+7);

    // cout << ps << "dp: " << dp[n][sum];
    // ps.pop_back();

    return dp[n][sum];
}

int powerMod(int a, int b, int mod) {
    if(b == 0) {
        return 1;
    }

    int halfPowerMod = powerMod(a, b >> 1, mod);
    if(b & 1) {
        return (1ll * a * halfPowerMod * halfPowerMod) % mod;
    }
    else {
        return (1ll * halfPowerMod * halfPowerMod) % mod;
    }
}

int divmod(int a, int b, int mod) {
    return (1ll * a * powerMod(b, mod-2, mod)) % mod;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, j;
    cin >> n;

    int sum = n * (n+1) / 2;

    if(sum & 1) {
        cout << "0\n";
        return 0;
    }

    vector<vector<int>> dp(n+1, vector<int>(sum/2+1, 0));
    int mod = int(1e9+7);
    // cout << divmod(solve(n, sum / 2, dp), 2, int(1e9+7)) << "\n";

    // for(i=0;i<=n;i++) {
    //     for(j=0;j<=sum/2;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // dp = vector<vector<int>>(n+1, vector<int>(sum/2+1));
    dp[0][0] = 1;
    for(i=1;i<=n;i++) {
        for(j=0;j<=sum/2;j++) {
            if(j == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = dp[i-1][j];
                if(j - i >= 0) {
                    dp[i][j] = (dp[i][j] + dp[i-1][j - i]) % mod;
                }
            }
        }
    }
    // for(i=0;i<=n;i++) {
    //     for(j=0;j<=sum/2;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    cout << divmod(dp[n][sum/2], 2, mod) << "\n";

    return 0;
}