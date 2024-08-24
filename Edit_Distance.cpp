#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int getEditDistance(string& a, string& b, int n, int m, vector<vector<int>>& dp) {

    if(n == 0) {
        return m;
    }

    if(m == 0) {
        return n;
    }

    if(dp[n-1][m-1] != -1) {
        return dp[n-1][m-1];
    }

    if(a[n-1] == b[m-1])
        return dp[n-1][m-1] = getEditDistance(a, b, n-1, m-1, dp);
    else
        return dp[n-1][m-1] = 1 + min({
            getEditDistance(a, b, n-1, m, dp),
            getEditDistance(a, b, n, m-1, dp),
            getEditDistance(a, b, n-1, m-1, dp)
        });
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    int n=s1.size(), m=s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    int i,j;
    for(i=0;i<=n;i++) {
        dp[i][0] = i;
    }
    for(i=0;i<=m;i++) {
        dp[0][i] = i;
    }

    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            if(s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({
                    dp[i-1][j],
                    dp[i][j-1],
                    dp[i-1][j-1]
                });
        }
    }

    cout << dp[n][m] << "\n";
    // cout << getEditDistance(s1, s2, n, m, dp) << "\n";

    return 0;
}