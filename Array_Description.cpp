#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int numberOfWaysForM(int a[], int ind, int no, int m, vector<vector<int>>& dp) {
    // ps.push_back('\t');
    // cout << ps << ind << " , " << a[ind] << " : " << no;
    if(a[ind] != 0 && a[ind] != no) {
        // ps.pop_back();
        return 0;
    }

    if(ind == 0) {
        return 1;
    }

    if(dp[ind][no] != -1) {
        return dp[ind][no];
    }

    int ans = 0, mod = int(1e9+7);
    if(no > 1) {
        ans = (ans + numberOfWaysForM(a, ind-1, no-1, m, dp)) % mod;
    }
    // cout << ps << "no-1(" << no-1 << ") : " << ans;
    ans = (ans + numberOfWaysForM(a, ind-1, no, m, dp)) % mod;
    // cout << ps << "no(" << no << ") : " << ans;
    if(no < m) {
        ans = (ans + numberOfWaysForM(a, ind-1, no+1, m, dp)) % mod;
    }
    // cout << ps << "no+1(" << no+1 << ") : " << ans;

    // ps.pop_back();
    return dp[ind][no] = ans;
}

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    int ans = 0, mod=int(1e9+7);
    vector<vector<int>> dp(n, vector<int>(m+1));

    if(a[0] == 0) {
        for(i=0;i<=m;i++) {
            dp[0][i] = 1;
        }
    }
    else {
        dp[0][a[0]] = 1;
    }

    for(i=1;i<n;i++) {
        if(a[i] == 0) {
            for(j=1;j<=m;j++) {
                if(j > 1)
                    dp[i][j] = (dp[i][j] + dp[i-1][j - 1]) % mod;
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
                if(j < m)
                    dp[i][j] = (dp[i][j] + dp[i-1][j + 1]) % mod;
            }
        }
        else {
            // cout << i << " : " << a[i] << " - ";
            if(a[i] > 1)
                dp[i][a[i]] = (dp[i][a[i]] + dp[i-1][a[i] - 1]) % mod;
            // cout << dp[i][a[i]] << " , ";
            dp[i][a[i]] = (dp[i][a[i]] + dp[i-1][a[i]]) % mod;
            // cout << dp[i][a[i]] << " , ";
            if(a[i] < m)
                dp[i][a[i]] = (dp[i][a[i]] + dp[i-1][a[i] + 1]) % mod;
            // cout << dp[i][a[i]] << "\n";
        }
    }

    // for(i=0;i<n;i++) { 
    //     for(j=0;j<=m;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for(i=1;i<=m;i++) {
        ans = (ans + dp[n-1][i]) % mod;
    }
    cout << ans << "\n";

    // for(i=1;i<=m;i++)
    //     ans = (ans + numberOfWaysForM(a, n-1, i, m, dp)) % int(1e9+7);

    // cout << ans << "\n";

    return 0;
}