#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int getMaximumPages(int h[], int s[], int ind, int tp, vector<vector<int>>& dp)
{
    if(tp <= 0 || ind < 0)
        return 0;

    if(dp[ind][tp] != -1) {
        return dp[ind][tp];
    }

    // ps.push_back('\t');
    // cout << ps << ind << " : " << tp;
    int take = 0;
    if(tp - h[ind] >= 0) {
        take = s[ind] + getMaximumPages(h, s, ind-1, tp - h[ind], dp);
    }
    // cout << ps << "t : " << take;
    int notTake = getMaximumPages(h, s, ind-1, tp, dp);
    // cout << ps << "nt : " << notTake;
    // ps.pop_back();

    return dp[ind][tp] = max(take, notTake);
}

int main()
{
    int i, j, n, x;
    cin >> n >> x;

    int h[n], s[n];
    for(i=0;i<n;i++) {
        cin >> h[i];
    }
    
    for(i=0;i<n;i++) {
        cin >> s[i];
    }

    vector<vector<int>> dp(n, vector<int>(x+1));
    // cout << getMaximumPages(h, s, n-1, x, dp) << "\n";
    // for(i=0;i<n;i++) {
    //     for(j=0;j<=x;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // dp = vector(n, vector<int>(x+1));

    for(i=0;i<n;i++) {
        for(j=0;j<=x;j++) {
            if(i == 0) {
                if(j - h[i] >= 0) {
                    dp[i][j] = s[i];
                }
            }
            else {
                if(j - h[i] >= 0) {
                    dp[i][j] = s[i] + dp[i-1][j - h[i]];
                }
                dp[i][j] = max(dp[i][j],dp[i-1][j]);
            }
            // cout << dp[i][j] << " ";
        }
        // cout << "\n";
    }

    cout << dp[n-1][x] << "\n";

    return 0;
}