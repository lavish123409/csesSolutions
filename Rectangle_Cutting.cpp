#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int rectangleCutting(int a, int b, vector<vector<int>>& dp) {

    if(a == b)
        return 0;

    if(dp[a][b] != -1)
        return dp[a][b];

    // if(a > b)
    //     swap(a, b);

    // ps.push_back('\t');
    // cout << ps << a << " , " << b;

    int i, ans=a+b;
    for(i=1;i<a;i++) {
        ans = min(ans, 1 + rectangleCutting(a-i, b, dp) + rectangleCutting(i, b, dp));
    }
    for(i=1;i<b;i++) {
        ans = min(ans, 1 + rectangleCutting(a, b-i, dp) + rectangleCutting(a, i, dp));
    }
    // cout << ps << "amns : " << ans;
    // ps.pop_back();
    return dp[a][b] = ans;

    // return 1 + rectangleCutting(b-a, a);

}

int main()
{
    int a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a+1, vector<int>(b+1));

    int i, j;
    for(i=1;i<=a;i++) { 
        for(j=1;j<=b;j++) {
            if(i == j) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = a + b;
            for(int k=1;k<i;k++) {
                dp[i][j] = min(dp[i][j], 1 + dp[i-k][j] + dp[k][j]);
            }
            for(int k=1;k<j;k++) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][j-k] + dp[i][k]);
            }
        }
    }

    cout << dp[a][b] << "\n";

    // cout << rectangleCutting(a, b, dp) << "\n";

    return 0;
}